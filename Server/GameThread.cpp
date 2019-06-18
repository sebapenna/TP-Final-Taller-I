#include <Common/exceptions.h>
#include <algorithm>
#include <iostream>
#include <chrono>
#include "GameThread.h"
#include "DTOProcessor.h"
#include "Stage.h"
#include "Player.h"

#define NEW_PLAYER_ADDED_MSG    "Nuevo jugador agregado a la partida\n"
#define PLAYER_DELETED_MSG    "Un jugador ha salido de la partida\n"
#define NEW_OWNER_MSG   "Ahora sos el owner de la partida, ingresa 's' para comenzar la partida\n"
#define OWNER_BEGAN_GAME   "Owner inicio la partida, presiona 's' para comenzar\n"

#define NEW_OWNER (uint8_t)  2
#define NOTIFICATION (uint8_t)  1
#define BEGIN_GAME  (uint8_t)   0

using namespace std::chrono;
using std::move;
using std::ref;
using std::lock_guard;
using std::mutex;
using std::cout;
using std::endl;
using std::for_each;
using std::shared_ptr;
using std::cerr;

void GameThread::sendToAllPlayers(std::shared_ptr<ProtocolDTO> &dto) {
    std::vector<size_t> to_delete;
    for_each(_players.begin(), _players.end(), [this, &dto, &to_delete] (Player* &player) {
        try {
            player->send(dto);
        } catch(FailedSendException& e) { // Medida seguridad, almaceno ids de clientes desonectados
            to_delete.push_back(player->id());
        }
    });
    // Elimino clientes que se desonectaron
    for_each(to_delete.begin(), to_delete.end(), [this](size_t &id) {deletePlayer(id);});
}

void GameThread::run(std::string map_filename) {
    try {
        Stage stage(map_filename);    // Creo stage en tiempo de espera al comienzo

        // Loop esperando a que owner inicie la partida. Verifico haya jugadores conectados
        while (!_begin_game && !_empty_game && !_game_finished) {
            std::this_thread::sleep_for(seconds(20)); // Duermo thread esperando el inicio
            auto event = _events_queue.getTopAndPop();
            if (event != nullptr)
                switch (event->getProtocolId()) {
                    case PROTOCOL_QUIT: // Jugador que salio de la partida
                        deletePlayer(event->getPlayerId()); // Elimino jugador de la partida
                        break;
                    case PROTOCOL_BEGIN:
                        if (event->getPlayerId() == 0) {  // Solo owner puede iniciar partida
                            _begin_game = true;
                            notifyOwnerBeganGame();
                        }
                        break;
                }
        }

        if (_begin_game && !_empty_game && !_game_finished) {
            stage.createChells(_players.size());    // Creo los chells determinados los jugadores

            // Envio escenario completo a cada jugador
            auto stage_dtos = stage.getInitialConfiguration();
            for_each(stage_dtos.begin(), stage_dtos.end(), [this](shared_ptr<ProtocolDTO> &dto) {
                    sendToAllPlayers(dto);
            });

            // Notifico a cada jugador su id
            std::vector<size_t> to_delete;
            for_each(_players.begin(), _players.end(), [this, &to_delete](Player* &player) {
                auto player_id_dto = DTOProcessor::createPlayerIdDTO(player->id());
                try {
                    player->send(player_id_dto);
                } catch(FailedSendException& e) {   // Cliente desconectado
                    to_delete.push_back(player->id());
                }
            });

            // Elimino posibles clientes que se desonectaron
            for_each(to_delete.begin(), to_delete.end(), [this](size_t &id) { deletePlayer(id); });
            // todo: SI MANTENGO ESTE VECTOR DEBERIA ELIMINAR SU CHELL DEL MAPA
            to_delete.clear();

            // Notifico a cada jugador que comienza la partida
            auto begin_dto = DTOProcessor::createBeginDTO();
            sendToAllPlayers(begin_dto);

            cout << "Comienza la partida " << _id << endl;


            // Loop mientras haya jugadores y no haya terminado el juego
            while (!_empty_game && !_game_finished) {
                auto start = high_resolution_clock::now();

                // Desencolo       //todo:TIMEOUT !
                for (auto e = _events_queue.getTopAndPop(); e; e = _events_queue.getTopAndPop()) {
                    stage.apply(e->getPtr().get(), e->getPlayerId());
                    if (e->getProtocolId() == PROTOCOL_QUIT)
                        deletePlayer(e->getPlayerId()); // Elimino jugador de la partida
                }

                // Step
                stage.step();

                // Notifico cambios a los jugadores
                auto dto_vector = stage.getUpdatedDTO();
                for_each(dto_vector.begin(), dto_vector.end(), [this](shared_ptr<ProtocolDTO>dto){
                    sendToAllPlayers(dto);
                }); // Envio DTO de objetos a actualizar

                dto_vector = stage.getDeletedDTO();
                for_each(dto_vector.begin(), dto_vector.end(), [this](shared_ptr<ProtocolDTO>dto){
                    sendToAllPlayers(dto);
                }); // Envio DTO de objetos a eliminar

                // Sleep
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);
                int sleep_time = (TIME_STEP) * 1000 - duration.count();
                if (sleep_time > 0)
                    std::this_thread::sleep_for(milliseconds(sleep_time));
            }
        }
        cout << "Partida "<<_id <<  " finalizada"<<endl;
        _dead_thread = true; // Registro que se llego al fin del thread
    } catch(const std::exception& e) {
        _dead_thread = true; // Registro que se llego al fin del thread
        cerr << "Game Thread: " << e.what();
    } catch(...) {
        _dead_thread = true; // Registro que se llego al fin del thread
        cerr << "Game Thread: " << UnknownException().what();
    }
}

// Todas los atributos se deben inicializar de esta manera antes del thread para ya estar
// disponibles cuando el  mismo comienze su ejecucion y no haya invalid reads
GameThread::GameThread(Player* new_player, const size_t &max_players, std::string map_filename,
        const size_t &id) : _map_filename(map_filename), _game_finished(false),
        _empty_game(false), _begin_game(false), _dead_thread(false), _max_players(max_players),
        _id(id), _gameloop(&GameThread::run, this, map_filename) {
    addPlayerIfOpenToNewPlayersAndNotFull(new_player);
}

bool GameThread::addPlayerIfOpenToNewPlayersAndNotFull(Player *new_player) {
    lock_guard<mutex> lock(_m);

    // Maximo de jugadores alcanzado o partida ya comenzo
    if (_players.size() >= _max_players || _begin_game) {

        return false;
    }
    new_player->setId(_players.size());

    if (new_player->id() != 0)   // No notifico cuando es el primer jugador
        notifyAllNewPlayer();

    _players.push_back(new_player);

    return true;
}

void GameThread::deletePlayer(const size_t &id) {
    lock_guard<mutex> lock(_m);

    _players.remove_if([this, &id](Player* p) {
        if (!_begin_game && p->id() > id) {
            // Actualizo ids mientras busco elemento, en caso de juego aun no inciado
            p->setId(p->id() - 1);
            return false;
        }
        return (p->id() == id) ? (p->disconnectAndJoin(), delete p, p = nullptr, true) : false;
    });

    notifyAllDeletedPlayer();
    if (id == 0)    // Elimine al owner, notifico al nuevo
        notifyNewOwner();

    if (_players.empty()) {   // Se desconectaron todos los jugadores
        _empty_game = true;
        _game_finished = true;
    }
}

const size_t GameThread::id() const {
    return _id;
}

SafeQueue<std::shared_ptr<Event>>& GameThread::getEventsQueue() {
    return _events_queue;
}

bool GameThread::isDead() {
    return _dead_thread;
}

void GameThread::endGameAndJoin() {
    _game_finished = true;
    _gameloop.join();

    // Una vez finalizado el gameloop elimino los jugadores
    std::for_each(_players.begin(), _players.end(), [](Player* &player) {
        player->disconnectAndJoin();
        delete player;
        player = nullptr;
    });
}

bool GameThread::openToNewPlayers() {
    return !_begin_game;    // Juego no comenzo
}

size_t GameThread::maxPlayers() {
    return _max_players;
}

size_t GameThread::playersJoined() {
    return _players.size();
}

std::string &GameThread::mapFileName() {
    return _map_filename;
}

void GameThread::notifyAllNewPlayer() {
    for_each(_players.begin(), _players.end(), [this] (Player* &player) {
            player->notify(NOTIFICATION, NEW_PLAYER_ADDED_MSG);
    });
}

void GameThread::notifyAllDeletedPlayer() {
    for_each(_players.begin(), _players.end(), [this] (Player* &player) {
        player->notify(NOTIFICATION, PLAYER_DELETED_MSG);
    });
}

void GameThread::notifyNewOwner() {
    if (!_players.empty()) {
        auto new_owner = _players.front();
        new_owner->notify(NEW_OWNER, NEW_OWNER_MSG);
    }
}

void GameThread::notifyOwnerBeganGame() {
    for_each(_players.begin(), _players.end(), [this] (Player* &player) {
        player->notify(BEGIN_GAME, OWNER_BEGAN_GAME);
    });
}
