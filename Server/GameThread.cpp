#include "GameThread.h"
#include "Stage.h"
#include "DTOProcessor.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <Common/exceptions.h>
#include "Player.h"


using namespace std::chrono;
using std::move;
using std::ref;
using std::lock_guard;
using std::mutex;
using std::cout;
using std::endl;
using std::for_each;
using std::shared_ptr;


// todo : NECESARIOS LOS CATCH EN SEND PARA ELIMINAR ?
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
        Stage stage(move(map_filename));    // Creo stage en tiempo de espera al comienzo

        // Loop esperando a que se indique que comienza la partida. Verifico no se hayan
        // desconectado todos los jugadores
        while (!_begin_game && !_empty_game && !_game_finished) {
            // todo: un sleep_for?
            auto event = _events_queue.getTopAndPop();  // todo: Cambiar, desencola todo el tiempo
            if (event != nullptr)  // Posible deseconexion
                switch (event->getProtocolId()) {
                    case PROTOCOL_QUIT:
                        deletePlayer(event->getPlayerId()); // Elimino jugador de la partida
                        break;
                    case PROTOCOL_BEGIN:
                        if (event->getPlayerId() == 0)  // Solo owner de partida puede iniciar
                            _begin_game = true;
                        break;
                }
        }
        if (_begin_game && !_empty_game) {
            stage.createChells(_players.size());    // Creo los chells determinados los jugadores

            // Envio escenario completo a cada jugador
            auto stage_dtos = stage.getInitialConfiguration();
            for_each(stage_dtos.begin(), stage_dtos.end(), [this](shared_ptr<ProtocolDTO> &dto) {
                    sendToAllPlayers(dto);
            });

            // Notifico a cada jugador su id
            std::vector<size_t> to_delete;
            for_each(_players.begin(), _players.end(), [this, &to_delete](Player* &player) {
                auto player_id_dto = DTOProcessor::createDTO(player->id());
                try {
                    player->send(player_id_dto);
                } catch(FailedSendException& e) {   // Cliente desconectado
                    to_delete.push_back(player->id());
                }
            });
            // Elimino clientes que se desonectaron
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
                for (auto event = _events_queue.getTopAndPop(); event;
                        event = _events_queue.getTopAndPop()) {
                    stage.apply(event->getPtr().get(), event->getPlayerId());
                    if (event->getProtocolId() == PROTOCOL_QUIT)
                        deletePlayer(event->getPlayerId()); // Elimino jugador de la partida
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







                /* todo: SACAR!!!!!!!!!!!!!!!!!! USO BEGIN PARA CORTAR RECEPCION EN CLIENT TEST*/
                for (auto &player : _players) {
                    auto dto = DTOProcessor::createBeginDTO();
//                    try {
                        player->send(dto);
//                    } catch(FailedSendException& e) {   // Cliente desconectado
//                        deletePlayer(player->id());
//                    }
                }









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
        cout << e.what();
    } catch(...) {
        cout << UnknownException().what();
    }
}

// Todas los atributos se deben inicializar de esta manera antes del thread para ya estar
// disponibles cuando el  mismo comienze su ejecucion y no haya invalid reads
GameThread::GameThread(Player* new_player, const size_t &max_players, std::string &&map_filename,
        const size_t &id) : _game_finished(false), _empty_game(false), _begin_game(false),
        _dead_thread(false), _max_players(max_players), _id(id),
        _gameloop(&GameThread::run, this, move(map_filename)) {
    addPlayerIfNotFull(new_player);
}

bool GameThread::addPlayerIfNotFull(Player* new_player) {
    lock_guard<mutex> lock(_m);
    if (_players.size() >= _max_players)    // Maximo de jugadores alcanzado
        return false;
    new_player->setId(_players.size());
    _players.push_back(new_player);
    return true;
}

void GameThread::deletePlayer(const size_t &id) {
    lock_guard<mutex> lock(_m);
    _players.remove_if([this, &id](Player* player) {
        if (!_begin_game && player->id() > id) {
            // Actualizo ids mientras busco elemento, en caso de juego aun no inciado
            player->setId(player->id() - 1);
            return false;
        }
        return (player->id() == id) ? (player->disconnectAndJoin(), delete player, player =
                nullptr, true) : false;
    });
    if (_players.empty()) {   // Se fueron todos los jugadpres
        _empty_game = true;
        _game_finished = true;
    }
}

void GameThread::beginGame() {
    _begin_game = true;
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

void GameThread::setId(const size_t &id) {
    _id = id;
}

void GameThread::endGameAndJoin() {
    // todo: notificar al cliente que termino ? Si, en el gameloop con un protocolo - si cierra el
    //  servidor tan solo recibira exception
    _game_finished = true;
    _gameloop.join();
    // Una vez finalizado el gameloop elimino los jugadores
    std::for_each(_players.begin(), _players.end(), [](Player* &player) {
        player->disconnectAndJoin();
        delete player;
        player = nullptr;
    });
}

// todo: posible race condition ?
bool GameThread::openToNewPlayers() {
    return _begin_game;
}
