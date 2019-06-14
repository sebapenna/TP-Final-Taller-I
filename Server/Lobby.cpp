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


void Lobby::runEraserThread() {
    while (!_connection_closed) {
        _games.erase(std::remove_if(_games.begin(), _games.end(), [](shared_ptr<GameThread> game) {
            return game->isDead();
        }), _games.end());
    }
}

Lobby::Lobby(const std::string &port) : _connection_closed(false), _next_player_id(0),
_accept_socket(port, WAITING_QUEUE_SIZE)/*, _game_eraser_thread(&Lobby::runEraserThread, this)*/ { }

void Lobby::shutdown() {
    _connection_closed = true;
    _accept_socket.shutdown();
    std::for_each(_players_in_lobby.begin(), _players_in_lobby.end(), [](Player *player) {
        delete player;
        player = nullptr;
    }); // Elimino jugadores que quedaban en lobby
    std::for_each(_games.begin(), _games.end(), [](shared_ptr<GameThread>  game) {
        game->endGameAndJoin();
    });
}

void Lobby::run() {
    // Loop va a finalizar cuando haga shutdown a Lobby, mientras tanto escucha conexiones
    try {
        while (!_connection_closed) {
            // Creo player en heap asi esta disponible para resto del programa al salir de scope
            Socket peer = _accept_socket.acceptConnection();

            // Permito que nuevos jugadores se conecten pero evito que se cree mas de un player en
            // el mismo insante
            _m.lock();
            Player *new_player = new Player(move(peer), ref(*this), _next_player_id);
            ++_next_player_id;  // Incremento hacia proximo a id
            _players_in_lobby.push_back(new_player);
            _m.unlock();
            cout << "Nuevo jugador conectado, creando partida..."<<endl;

            // todo: que se actualizen los id de las partidas a medida que se eliminan (simil
            //  players)
        }
    } catch(const CantConnectException& e) { }  // Socket aceptador cerrado
}

SafeQueue<std::shared_ptr<Event>> &Lobby::createGame(Player* player,
        const size_t &n_players, string &&map_filename) {
    // Evito que se creen varias varios GameThread al mismo tiempo y posible race condition al
    // agregar al vector y asignar un id a la partida. Hasta este punto cada jugador tiene una
    // conexion por separado con el servidor, por lo tanto la simultanea creacion de partidas no
    // se ve afectada, tan solo la creacion del Thread.
    std::lock_guard<std::mutex> lock(_m);
    // Id de la partida sera en base al tamaño del vector
    auto new_game = std::make_shared<GameThread>(player, n_players, move(map_filename),
            _games.size());

    _players_in_lobby.erase(std::remove_if(_players_in_lobby.begin(), _players_in_lobby.end(),
            [player](Player *p) {
        return player->id() == p->id();
    }), _players_in_lobby.end());     // Elimino player del lobby

    _games.push_back(new_game);
    return ref(new_game->getEventsQueue());
}

SafeQueue<std::shared_ptr<Event>> &Lobby::joinGame(Player* player,
        const size_t &game_id) {
    // Evito que varios jugadores intenten unirse a una misma partida al mismo tiempo, rompiendo
    // posiblemente el limite de jugadores dentro de la misma.
    std::lock_guard<std::mutex> lock(_m);
    auto game = _games.at(game_id);
    if (game->addPlayerIfNotFull(player)) {
        _players_in_lobby.erase(std::remove_if(_players_in_lobby.begin(), _players_in_lobby.end(),
                [player](Player *p) {
            return player->id() == p->id();
        }), _players_in_lobby.end());     // Elimino player del lobby
        return ref(game->getEventsQueue());
    }
    throw FullGameException();
}



//todo: limite de nuevas partidas
//bool Lobby::gamesLimitReached() {
//    return _active_games == CONCURRENT_GAMES_LIMIT;
//}

// todo: thread que elimina games terminados