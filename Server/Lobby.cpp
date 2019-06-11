#include "Lobby.h"
#include "Player.h"
#include <Common/exceptions.h>

#define WAITING_QUEUE_SIZE  10
#define CONCURRENT_GAMES_LIMIT  3

using std::move;

Lobby::Lobby(const std::string &port) : _accept_socket(port, WAITING_QUEUE_SIZE) { }

void Lobby::shutdown() {
    // todo: aca hago join de los threads
    _accept_socket.shutdown();
}

void Lobby::run() {
    // Loop va a finalizar cuando haga shutdown a Lobby, mientras tanto escucha conexiones
    while (true) {
        try {
            Player new_player(move(_accept_socket.acceptConnection()));
            GameThread new_thread(move(new_player), 1, "filea.yaml");
            // todo: contacto con cliente (thread aparte?). NUEVA_PARTIDA O CONECTARSE_A_UNA?
            // todo: que seleccione mapa
            // if (new_game)
            //  GameThread new_game(new_player, move(map_filename));
            // else
            //  _games.addPlayer(move(new_player))

        } catch(const CantConnectException& e) {
//                  No se aceptan mas conexiones
        }
    }
}

//bool Lobby::gamesLimitReached() {
//    return _active_games == CONCURRENT_GAMES_LIMIT;
//}
