#include "Lobby.h"
#include "Player.h"
#include <Common/exceptions.h>
#include <iostream>

#define WAITING_QUEUE_SIZE  10
#define CONCURRENT_GAMES_LIMIT  3

using std::cout;
using std::endl;
using std::move;
using std::shared_ptr;
using std::ref;
using std::make_shared;

Lobby::Lobby(const std::string &port) : _accept_socket(port, WAITING_QUEUE_SIZE) { }

void Lobby::shutdown() {
    _connection_closed = true;
    _accept_socket.shutdown();
    std::for_each(_games.begin(), _games.end(), [](shared_ptr<GameThread> &game) {
        game->endGame();
    });
}

void Lobby::run() {
    // Loop va a finalizar cuando haga shutdown a Lobby, mientras tanto escucha conexiones
    try {
        while (!_connection_closed) {
            // Creo player en heap asi esta disponible para resto del programa al salir de scope
            Socket peer = _accept_socket.acceptConnection();
            Player *new_player = new Player(move(peer), ref(*this));
//            auto new_player = make_shared<Player>(move(_accept_socket.acceptConnection()), ref(*this));

//            _waiting_players.push_back(new_player);
            cout << "Nuevo jugador conectado, creando partida..."<<endl;

            // todo: que se actualizen los id de las partidas a medida que se eliminan (simil
            //  players)

            // todo: contacto con cliente (thread aparte?). NUEVA_PARTIDA O CONECTARSE_A_UNA?
            // todo: que seleccione mapa => TODO ESTO EN PLAYER.HANDSHAKE
            // if (new_game)
            //  GameThread new_game(new_player, move(map_filename));
            // else
            //  _games.addPlayerIfNotFull(move(new_player))
        }
    } catch(const CantConnectException& e) { }  // Socket aceptador cerrado
}

SafeQueue<std::shared_ptr<Event>> &Lobby::createGame(/*std::shared_ptr<Player>*/Player* player,
        const size_t &n_players, string &&map_filename) {
    // Evito que se creen varias varios GameThread al mismo tiempo y posible race condition al
    // agregar al vector y asignar un id a la partida. Hasta este punto cada jugador tiene una
    // conexion por separado con el servidor, por lo tanto la simultanea creacion de partidas no
    // se ve afectada, tan solo la creacion del Thread.
    std::lock_guard<std::mutex> lock(_m);
    // id de la partida sera en base al tamaño del vector
    auto new_game = std::make_shared<GameThread>(player, n_players, move(map_filename),
            _games.size());
    _games.push_back(new_game);


//    _waiting_players.erase(std::remove_if(_waiting_players.begin(), _waiting_players.end(),
//            [player](shared_ptr<Player> &p) {
//        return p->id() == player->id();
//    }), _waiting_players.end());


    return ref(new_game->getEventsQueue());
}

SafeQueue<std::shared_ptr<Event>> &Lobby::joinGame(/*std::shared_ptr<Player>*/Player* player,
        const size_t &game_id) {
    // Evito que varios jugadores intenten unirse a una misma partida al mismo tiempo, rompiendo
    // posiblemente el limite de jugadores dentro de la misma.
    std::lock_guard<std::mutex> lock(_m);
    auto game = _games.at(game_id);
    if (game->addPlayerIfNotFull(player))
        return ref(game->getEventsQueue());
    throw FullGameException();
}


//todo: limite de nuevas partidas
//bool Lobby::gamesLimitReached() {
//    return _active_games == CONCURRENT_GAMES_LIMIT;
//}
