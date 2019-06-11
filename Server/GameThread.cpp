#include "GameThread.h"
#include "Stage.h"
#include "DTOProcessor.h"
#include <algorithm>
#include <chrono>

using namespace std::chrono;
using std::remove_if;
using std::move;
using std::ref;
using std::lock_guard;
using std::mutex;

// SEGUNDO: envio id a cada jugador ?
// TERCERO: comienza game loop?
void GameThread::run(std::string map_filename) {
    try {
        Stage stage(move(map_filename));    // Creo stage en tiempo de espera al comienzo

        // Loop esperando a que se indique que comienza la partida. Verifico no se hayan
        // desconectado todos los jugadores
        while (!_begin_game && !_players.empty()) {
            auto event = _events_queue.getTopAndPop();
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
        if (!_players.empty()) {    // Verifico que hay jugadores
            // Creo los chells una vez determinada la cantidad final de jugadores
            stage.createChells(_players.size());

            // Envio escenario completo a cada jugador
            auto stage_dtos = stage.getInitialConfiguration();
            for (auto &stage_object_dto : stage_dtos)
                for (auto &player : _players)
                    player.send(stage_object_dto);

            // Notifico a cada jugador su id
            for (auto &player : _players) {
                auto dto = DTOProcessor::createDTO(player.id());
                player.send(dto);
            }
            /* Enviada toda la configuracion para jugar */


            // todo: for (x in players) x.send(BEGINGAME)         /* INICIA JUEGO */

            // Loop mientras haya jugadores y no haya terminado el juego
            while (!_players.empty() && _game_finished) {
                auto start = high_resolution_clock::now();

                // Desencolo       //todo:TIMEOUT !
                for (auto event = _events_queue.getTopAndPop(); event; event = _events_queue
                        .getTopAndPop()) {
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
    ReceiverThread new_thread(ref(new_player), ref(_events_queue));
    _receive_threads.push_back(move(new_thread));
    new_player.setId(_players.size());
    _players.push_back(move(new_player));
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
}

void GameThread::beginGame() {
    lock_guard<mutex> lock(_m);
    _begin_game = true;
}

void GameThread::endGame() {
    lock_guard<mutex> lock(_m);
    _game_finished = true;
}
