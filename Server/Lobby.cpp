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
    _connection_closed = false;
    while (!_connection_closed) {
        // Duermo therad para evitar constantemente buscar partidas eliminadas
        std::unique_lock<std::mutex> lck(_mtx_sleep);
        _cv.wait_for(lck, std::chrono::minutes(1), [this]{return _connection_closed;});
        _games.erase(std::remove_if(_games.begin(), _games.end(), [](shared_ptr<GameThread> game) {
            if (game->isDead()) {
                game->endGameAndJoin();
                return true;
            }
            return false;
        }), _games.end());
        //todo: _players_joining para evitar race condition con games id

        // Actualizo id de partidas existentes para que concuerden con posicion en vector
        for (size_t new_id = 0; new_id < _games.size(); ++new_id)
            _games[new_id]->setId(new_id);
    }
}

Lobby::Lobby(const std::string &port) : _connection_closed(false), _next_player_id(0),
_accept_socket(port, WAITING_QUEUE_SIZE), _game_eraser_thread(&Lobby::runEraserThread, this) { }

void Lobby::shutdown() {
    _connection_closed = true;
    _cv.notify_one();   // Notifico a waitfor condicion modificada
    _game_eraser_thread.join();
    _accept_socket.shutdown();
    std::for_each(_players_in_lobby.begin(), _players_in_lobby.end(), [](Player *player) {
        player->disconnectAndJoin();    // Dejo que finaliza correctamente thread del cliente
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
        }
    } catch(const CantConnectException& e) { }  // Socket aceptador cerrado
}

SafeQueue<shared_ptr<Event>> &Lobby::createGame(Player* player,
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

SafeQueue<shared_ptr<Event>> &Lobby::joinGameIfNotFull(Player *player,
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

std::vector<std::tuple<size_t, size_t, size_t, std::string>> Lobby::getOpenGamesInformation() {

}
