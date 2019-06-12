#ifndef PORTAL_LOBBY_H
#define PORTAL_LOBBY_H

#include <Common/AcceptSocket.h>
#include <vector>
#include "GameThread.h"

// Servidor que acepta conexiones
class Lobby {
private:
    AcceptSocket _accept_socket;
    std::vector<std::shared_ptr<GameThread>> _games;
    bool _connection_closed = false;
//    size_t _active_games;

public:
    explicit Lobby(const std::string &port);

    void shutdown();

    void run();

//    bool gamesLimitReached();

// todo: loby.addGame ? => podria tener race condition
};


#endif //PORTAL_LOBBY_H
