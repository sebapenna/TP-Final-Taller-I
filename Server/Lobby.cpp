#include "Lobby.h"
#include "Player.h"
#include <Common/exceptions.h>
#include <iostream>

#define WAITING_QUEUE_SIZE  10
#define CONCURRENT_GAMES_LIMIT  3

using std::cout;
using std::endl;
using std::move;

Lobby::Lobby(const std::string &port) : _accept_socket(port, WAITING_QUEUE_SIZE) { }

void Lobby::shutdown() {
    _connection_closed = true;
    _accept_socket.shutdown();
    for (auto &game : _games) {
        game->endGame();
        game->join();
    }
}

void Lobby::run() {
    // Loop va a finalizar cuando haga shutdown a Lobby, mientras tanto escucha conexiones
    while (!_connection_closed) {
        try {
            cout << endl << "Esperando nuevo jugador..." << endl;

            auto ptr = std::make_shared<Player>(move(_accept_socket.acceptConnection()));

            cout << "Nuevo jugador conectado, creando partida..."<<endl;

            auto new_thread = std::make_shared<GameThread>(ptr, 1, std::move("filea.yaml"));
            _games.push_back(new_thread);

            cout << "Partida creada"<<endl;
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
