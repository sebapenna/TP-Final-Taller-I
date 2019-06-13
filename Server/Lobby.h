#ifndef PORTAL_LOBBY_H
#define PORTAL_LOBBY_H

#include <Common/AcceptSocket.h>
#include <vector>
#include "GameThread.h"
#include <memory>
#include "Event.h"
#include <Common/SafeQueue.h>
#include <mutex>

class Player;

// Servidor que acepta conexiones
class Lobby {
private:
    std::mutex _m;
    AcceptSocket _accept_socket;
    std::vector<std::shared_ptr<GameThread>> _games;
    bool _connection_closed = false;

public:
    explicit Lobby(const std::string &port);

    void shutdown();

    void run();

    // todo: createGameIfNotFull y que retorne exception como joinGame => CATCH EN PLAYER
    // Crea un nuevo GameThread. Retorna la cola de eventos de la partida
    SafeQueue<std::shared_ptr<Event>> &createGame(Player* player, const size_t &n_players,
            std::string &&map_filename);

    // Une en al jugador a la partida del id indicado y retorna la cola de eventos de dicha partida.
    // En caso de no haber podido unir al jugador se retorna nullptr
    SafeQueue<std::shared_ptr<Event>> &joinGame(Player* player, const size_t &game_id);

//    bool gamesLimitReached();
};


#endif //PORTAL_LOBBY_H
