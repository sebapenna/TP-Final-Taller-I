#include "GameThread.h"
#include "Stage.h"
#include "DTOProcessor.h"
#include <algorithm>
#include <chrono>
#include <iostream>


using namespace std::chrono;
using std::remove_if;
using std::move;
using std::ref;
using std::lock_guard;
using std::mutex;
using std::cout;
using std::endl;

// SEGUNDO: envio id a cada jugador ?
// TERCERO: comienza game loop?
void GameThread::run(std::string map_filename) {
    try {
        cout << "Creando stage..."<<endl;
        Stage stage(move(map_filename));    // Creo stage en tiempo de espera al comienzo
        cout << "Stage creado..."<<endl;

        // Loop esperando a que se indique que comienza la partida. Verifico no se hayan
        // desconectado todos los jugadores

        cout << "Esperando que owner de la partida decida comenzarla..."<<endl;
        while (!_begin_game && !_empty_game) {
            auto event = _events_queue.getTopAndPop();

            if (event != nullptr) { // Posible deseconexion
                std::cout << "DTO desencolado" << std::endl;

                switch (event->getProtocolId()) {
                    case PROTOCOL_QUIT:
                        deletePlayer(event->getPlayerId()); // Elimino jugador de la partida
                        break;
                    case PROTOCOL_BEGIN: {
                        cout << "Players size: "<<_players.size()<<endl;
                        cout << "Iniciando Partida..."<<endl;
                        if (event->getPlayerId() == 0)  // Solo owner de partida puede iniciar
                            _begin_game = true;
                        break;
                    }
                }
            }
        }
        if (!_empty_game) {    // Verifico que hay jugadores
            // Creo los chells una vez determinada la cantidad final de jugadores
            stage.createChells(_players.size());

            // Envio escenario completo a cada jugador
            auto stage_dtos = stage.getInitialConfiguration();
            for (auto &stage_object_dto : stage_dtos)
                for (auto &player : _players)
                    player.send(stage_object_dto);

            // Notifico a cada jugador su id
            for (auto &player : _players) {
                auto dto = DTOProcessor::createDTO(player.id());    // todo: ELIMINAR DOBLE DEF
                player.send(dto);
            }
            /* Enviada toda la configuracion para jugar */

            cout << "Configuracion inicial y IDs enviados"<<endl;

            // Notifico a cada jugador que comienza la partida
            for (auto &player : _players) {
                auto dto = DTOProcessor::createBeginDTO(); // todo: ELIMINAR DEF2 -unir con send_id?
                player.send(dto);
            }

            cout << "Comienza la partida" << endl;


            // Loop mientras haya jugadores y no haya terminado el juego
            while (!_empty_game && _game_finished) {
                auto start = high_resolution_clock::now();

                // Desencolo       //todo:TIMEOUT !
                for (auto event = _events_queue.getTopAndPop(); event; event =
                        _events_queue.getTopAndPop()) {
                    stage.apply(event->getPtr().get(), event->getPlayerId());
                    if (event->getProtocolId() == PROTOCOL_QUIT)
                        deletePlayer(event->getPlayerId()); // Elimino jugador de la partida
                }

                // Step
                stage.step();

                // Notifico cambios a los jugadores
                for (auto &dto : stage.getUpdatedDTO()) {   // Envio DTO de objetos a actualizar
                    for (auto &player : _players)
                        player.send(dto);
                }
                for (auto &dto : stage.getDeletedDTO()) {   // Envio DTO de objetos a eliminar
                    for (auto &player : _players)
                        player.send(dto);
                }








                /* todo: SACAR!!!!!!!!!!!!!!!!!! USO BEGIN PARA CORTAR RECEPCION EN CLIENT TEST*/
                for (auto &player : _players) {
                    auto dto = DTOProcessor::createBeginDTO();
                    player.send(dto);
                }









                // Sleep
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<seconds>(stop - start);
                int sleep_time = TIME_STEP - duration.count();
                if (sleep_time > 0)
                    std::this_thread::sleep_for(seconds(sleep_time));
            }
        }
    } catch(const std::exception& e) {
        throw;
    } catch(...) {
        throw;
    }

}

GameThread::GameThread(Player &&new_player, const size_t& max_players, std::string &&map_filename) :
_map_filename(move(map_filename)), _gameloop(&GameThread::run, this, move(map_filename)),
_max_players(max_players) {
    addPlayer(move(new_player));
}


void GameThread::addPlayer(Player &&new_player) {
    lock_guard<mutex> lock(_m);
    new_player.setId(_players.size());
    _players.push_back(move(new_player));

    auto it = _players.begin();
    std::advance(it, (_players.size() - 1)); // Obtengo el ultimo jugador almacenado

    ReceiverThread new_thread(ref(*it), ref(_events_queue));
    _receive_threads.push_back(move(new_thread));
}

// todo: THREAD QUE CONTROLE SI RECEIVER_THREAD IS_ALIVE (jugador no corto conexion) => IF DEAD
//  DELETE_PLAYER

void GameThread::deletePlayer(const size_t &id) {
    // todo: eliminar threads. Necesario? No se van a agregar jugadores
    lock_guard<mutex> lock(_m);
//    for (auto &thread : _receive_threads)
//        if (thread.getPlayerId() == id)
//            thread.join();  // Termino ejecucion del thread
//    _receive_threads.erase(remove_if(_receive_threads.begin(), _receive_threads.end(),
//            &ReceiverThread::isDead), _receive_threads.end());
    _players.remove_if([this, &id](Player &player) {
        if (!_begin_game && player.id() > id) // Actualizo ids mientras busco elemento, en caso de juego aun no inciado
            player.setId(player.id() - 1);
        return player.id() == id;
    });
    if (_players.empty())   // Se fueron todos los jugadpres
        _empty_game = true;
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
    for (auto &thread : _receive_threads)
        thread.join();
    _gameloop.join();
}

GameThread &GameThread::operator=(GameThread &&other) {
    if (this == &other)
        return *this;
    cout << endl<<"ENTRA: "<<other._players.size()<<endl;

    _gameloop = move(other._gameloop);
//    _events_queue = std::move(other._events_queue);
    _players = move(other._players);
    _receive_threads = move(other._receive_threads);
    _max_players = other._max_players;
    _begin_game = other._begin_game;
    _game_finished = other._game_finished;
    _map_filename = move(other._map_filename);
    cout << "adentro size: "<<_players.size()<<endl;
    cout << "adentro other size: "<<other._players.size()<<endl;

//    other._players.clear();
    other._max_players = -1;
    other._begin_game = false;
    other._game_finished = false;
    other._map_filename.clear();
    return *this;
}

GameThread::GameThread(GameThread &&other) {
    *this = move(other);
}
