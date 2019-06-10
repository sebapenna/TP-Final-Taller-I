#ifndef PORTAL_LOBBY_H
#define PORTAL_LOBBY_H

#include <Common/AcceptSocket.h>
#include <vector>
#include "GameThread.h"

// Servidor que acepta conexiones
class Lobby {
private:
    AcceptSocket _accept_socket;
    std::vector<GameThread> _games;
//    size_t _active_games;

public:
    explicit Lobby(const std::string &port);

    void shutdown();

    void run();

//    bool gamesLimitReached();
};


#endif //PORTAL_LOBBY_H
