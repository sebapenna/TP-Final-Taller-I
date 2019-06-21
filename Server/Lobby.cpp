#include "Lobby.h"
#include "Player.h"
#include <Common/exceptions.h>
#include <iostream>

#define WAITING_QUEUE_SIZE  10

using std::cout;
using std::cerr;
using std::endl;
using std::move;
using std::shared_ptr;
using std::ref;
using std::make_shared;


void Lobby::runEraserThread() {
    try {
        _connection_closed = false;
        while (!_connection_closed) {
            // Duermo therad para evitar constantemente buscar partidas eliminadas
            std::unique_lock<std::mutex> lck(_mtx_sleep);
            _cv.wait_for(lck, std::chrono::milliseconds(500), [this]{return _connection_closed;});

            _games.erase(std::remove_if(_games.begin(), _games.end(), [](shared_ptr<GameThread> game) {
                return (game->isDead()) ? (game->endGameAndJoin(), true) : false;
            }), _games.end());
        }
    } catch(const exception& e) {
        cerr << "Hilo controlador de juegos finalizados: " << e.what();
    } catch(...) {
        cerr << "Hilo controlador de juegos finalizados: " << UnknownException().what();
    }
}

Lobby::Lobby(const std::string &port) : _connection_closed(false), _next_player_id(0),
_next_game_id(0), _accept_socket(port, WAITING_QUEUE_SIZE),
_game_eraser_thread(&Lobby::runEraserThread, this) { }

void Lobby::shutdown() {
    _connection_closed = true;
    _cv.notify_one();   // Notifico a waitfor que condicion fue modificada

    _game_eraser_thread.join();
    _accept_socket.shutdown();

    std::for_each(_players_in_lobby.begin(), _players_in_lobby.end(), [](Player *player) {
        player->disconnectAndJoin();    // Dejo que finalize correctamente thread del cliente
        delete player;
        player = nullptr;
    }); // Elimino jugadores que quedaban en lobby, todavia no presentes en partidas

    std::for_each(_games.begin(), _games.end(), [](shared_ptr<GameThread>  game) {
        game->endGameAndJoin();
    });
}

void Lobby::run() {
    try {
        while (!_connection_closed) {
            Socket peer = _accept_socket.acceptConnection();

            // Creo player en heap asi esta disponible para resto del programa al salir de scope
            Player *new_player = new Player(move(peer), ref(*this), _next_player_id);
            ++_next_player_id;  // Incremento hacia proximo a id
            _players_in_lobby.push_back(new_player);

            cout << "Nuevo jugador conectado"<<endl;
        }
    } catch(const CantConnectException& e) {
        cerr << "Socket aceptador cerrado\n";
    }  // Socket aceptador cerrado
}

SafeQueue<shared_ptr<Event>> &Lobby::createGame(Player* player, const size_t &n_players,
        string &&map_filename) {
    // Evito que se creen varias varios GameThread al mismo tiempo y posible race condition al
    // agregar al vector y asignar un id a la partida. Hasta este punto cada jugador tiene una
    // conexion por separado con el servidor, por lo tanto la simultanea creacion de partidas no
    // se ve afectada, tan solo la creacion del Thread.
    std::lock_guard<std::mutex> lock(_m);
    // Id de la partida sera en base al tamaño del vector
    auto game = std::make_shared<GameThread>(player, n_players, move(map_filename), _next_game_id);
    ++_next_game_id; // Actualizo proximo id

    // Elimino player del lobby
    _players_in_lobby.erase(std::remove_if(_players_in_lobby.begin(), _players_in_lobby.end(),
            [player](Player *p) { return player->id() == p->id(); }), _players_in_lobby.end());

    _games.push_back(game);
    return ref(game->getEventsQueue());
}

SafeQueue<shared_ptr<Event>> &Lobby::joinGameIfOpenAndNotFull(Player *player, const size_t &game_id) {
    // Evito que varios jugadores intenten unirse a una misma partida al mismo tiempo, rompiendo
    // posiblemente el limite de jugadores dentro de la misma.
    std::lock_guard<std::mutex> lock(_m);

    // todo: optimizar con binary search
    auto it = std::find_if(_games.begin(), _games.end(), [game_id](shared_ptr<GameThread> g) {
        return g->id() == game_id;
    });
    if (it == _games.end()) // Se elimino partida
        throw CantJoinGameException();

    auto game = *it;
    if (game->addPlayerIfOpenToNewPlayersAndNotFull(player)) {    // Primero compruebo id
        _players_in_lobby.erase(remove_if(_players_in_lobby.begin(), _players_in_lobby.end(),
                [player](Player *p) {
            return player->id() == p->id();
        }), _players_in_lobby.end());     // Elimino player del lobby
        return ref(game->getEventsQueue());
    }

    throw CantJoinGameException();
}

std::vector<std::tuple<size_t, size_t, size_t, std::string>> Lobby::getOpenGamesInformation() {
    // GameId - MaxPlayers - PlayersAdded - MapName
    std::vector<std::tuple<size_t, size_t, size_t, std::string>> output;
    for (auto &g : _games)
        if (g->openToNewPlayers())
            output.emplace_back(g->id(), g->maxPlayers(), g->playersJoined(), g->mapFileName());
    return move(output);
}
