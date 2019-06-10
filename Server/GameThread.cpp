#include "GameThread.h"
#include <algorithm>

using std::remove_if;
using std::move;
using std::ref;
using std::lock_guard;
using std::mutex;

void GameThread::run() {
    try {
        while (!_begin_game) { }    // Loop esperando a que se indica que comienza la partida
        // CERO: leo archivo yaml y creo en world => YA LO HACE STAGE
        // PRIMERO: envio todos los datos de stage
        // SEGUNDO: envio id a cada jugador ?
        // TERCERO: comienza game loop?

        // Stage(fname)
        // stage.getDTOsToSend() => vector<ProtocolDTO>
        // for (x int v) { for (player in players) player.send(x) }
        // for (x in players) x.send(player_id)
        /* HASTA ACA DATA INICIAL */

        // for (x in players) x.send(BEGINGAME)
        /* INICIA JUEGO */

        // while() {    // while players != 0? y otra condicion
        //      desencolar
        //      apply(n)
        //      step
        //      sleep
        // }
    } catch(const std::exception& e) {
        throw;
    } catch(...) {
        throw;
    }

}

GameThread::GameThread(Player &&new_player, std::string map_filename) :
_map_filename(move(map_filename)), _gameloop(&GameThread::run, this) {
    addPlayer(move(new_player));
}

void GameThread::addPlayer(Player &&new_player) {
    lock_guard<mutex> lock(_m);
    ReceiverThread new_thread(ref(new_player), ref(_events_queue));
    _receive_threads.push_back(move(new_thread));
    new_player.setId(_players.size());
    _players.push_back(move(new_player));
}

void GameThread::deletePlayer(const size_t &id) {
    // todo: eliminar threads. Necesario? No se van a agregar jugadores
//    lock_guard<mutex> lock(_m);
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
