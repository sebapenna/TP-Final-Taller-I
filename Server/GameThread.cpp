#include "GameThread.h"
#include "Stage.h"
#include "DTOProcessor.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <Common/exceptions.h>


using namespace std::chrono;
using std::move;
using std::ref;
using std::lock_guard;
using std::mutex;
using std::cout;
using std::endl;
using std::for_each;
using std::shared_ptr;


void GameThread::sendToAllPlayers(std::shared_ptr<ProtocolDTO> &dto) {
    for_each(_players.begin(), _players.end(), [this, &dto]
            (shared_ptr<Player> &player) { player->send(dto);});
}

void GameThread::run(std::string map_filename) {
    try {
        Stage stage(move(map_filename));    // Creo stage en tiempo de espera al comienzo

        // Loop esperando a que se indique que comienza la partida. Verifico no se hayan
        // desconectado todos los jugadores
        cout << "Esperando que owner de la partida decida comenzarla..."<<endl;
        while (!_begin_game && !_empty_game) {
            // todo: un sleep_for?
            auto event = _events_queue.getTopAndPop();  // todo: Cambiar, desencola todo el tiempo
            if (event != nullptr) { // Posible deseconexion
                switch (event->getProtocolId()) {
                    case PROTOCOL_QUIT:
                        deletePlayer(event->getPlayerId()); // Elimino jugador de la partida
                        break;
                    case PROTOCOL_BEGIN: {
                        if (event->getPlayerId() == 0)  // Solo owner de partida puede iniciar
                            _begin_game = true;
                        break;
                    }
                }
            }
        }
        if (!_empty_game) {    // Verifico que hay jugadores
            cout << "Iniciando Partida..."<<endl;
            // Creo los chells una vez determinada la cantidad final de jugadores
            stage.createChells(_players.size());

            // Envio escenario completo a cada jugador
            auto stage_dtos = stage.getInitialConfiguration();
            for_each(stage_dtos.begin(), stage_dtos.end(), [this](shared_ptr<ProtocolDTO> &dto) {
                    sendToAllPlayers(dto);
            });

            // Notifico a cada jugador su id
            for_each(_players.begin(), _players.end(), [this](shared_ptr<Player> &player) {
                auto player_id_dto = DTOProcessor::createDTO(player->id());
                player->send(player_id_dto);
            });

            // Enviada toda la configuracion para jugar
            cout << "Configuracion inicial y IDs enviados"<<endl;

            // Notifico a cada jugador que comienza la partida
            auto begin_dto = DTOProcessor::createBeginDTO();
            sendToAllPlayers(begin_dto);

            cout << "Comienza la partida" << endl;


            // Loop mientras haya jugadores y no haya terminado el juego
            while (!_empty_game && !_game_finished) {
                auto start = high_resolution_clock::now();

                // Desencolo       //todo:TIMEOUT !
                for (auto event = _events_queue.getTopAndPop(); event; event = _events_queue.getTopAndPop()) {
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
                    player->send(dto);
                }









                // Sleep
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);
                int sleep_time = (TIME_STEP) * 1000 - duration.count();
                if (sleep_time > 0)
                    std::this_thread::sleep_for(milliseconds(sleep_time));
            }
        }
        cout << "Partida finalizada"<<endl;
        _game_finished = true; // todo: necesario aca?
    } catch(const std::exception& e) {
        cout << e.what();
    } catch(...) {
        cout << UnknownException().what();
    }
}

GameThread::GameThread(std::shared_ptr<Player> new_player, const size_t &max_players,
                       std::string &&map_filename, const size_t &id) :
_map_filename(move(map_filename)), _gameloop(&GameThread::run, this, move(map_filename)),
_max_players(max_players), _id(id) {
    addPlayer(move(new_player));
}


void GameThread::addPlayer(std::shared_ptr<Player> new_player) {
    lock_guard<mutex> lock(_m);
    new_player->setId(_players.size());
    _players.push_back(new_player);
    // todo: mover a Player
    auto new_thread = std::make_shared<ReceiverThread>(new_player, ref(_events_queue));
    _receive_threads.push_back(move(new_thread));
}

// todo: THREAD QUE CONTROLE SI RECEIVER_THREAD IS_ALIVE (jugador no corto conexion) => IF DEAD
//  DELETE_PLAYER

void GameThread::deletePlayer(const size_t &id) {
    // todo: eliminar threads. Necesario? No se van a agregar jugadores (durante partida, antes si)
    lock_guard<mutex> lock(_m);
//    for (auto &thread : _receive_threads)
//        if (thread.getPlayerId() == id)
//            thread.join();  // Termino ejecucion del thread
//    _receive_threads.erase(remove_if(_receive_threads.begin(), _receive_threads.end(),
//            &ReceiverThread::isDead), _receive_threads.end());
    _players.remove_if([this, &id](std::shared_ptr<Player> player) {
        if (!_begin_game && player->id() > id) // Actualizo ids mientras busco elemento, en caso de juego aun no inciado
            player->setId(player->id() - 1);
        return player->id() == id;
    });
    if (_players.empty()) {   // Se fueron todos los jugadpres
        _empty_game = true;
        _game_finished = true;
    }
}

void GameThread::beginGame() {
    lock_guard<mutex> lock(_m);
    _begin_game = true;
}

void GameThread::endGame() {
    // todo: notificar al cliente que termino ?
    lock_guard<mutex> lock(_m);
    _game_finished = true;
}

void GameThread::join() {
    _gameloop.join();
    std::for_each(_receive_threads.begin(), _receive_threads.end(),
            [](std::shared_ptr<ReceiverThread> &thread) {thread->join();});
}

const size_t GameThread::id() const {
    return _id;
}


