//
// Created by jonathanmedina on 24/06/19.
//

#ifndef PORTAL_GAMECONTROLLER_H
#define PORTAL_GAMECONTROLLER_H


#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include <Common/ProtectedBlockingQueue.h>
#include "SDL_Runner.h"

class GameController {
private:
    SDL_Runner& sdlRunner;
    ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>>& blockingQueue;
    bool& done;
    void positionInScreen(int& x, int& y, SDL_Runner& sdlRunner);
public:
    GameController(SDL_Runner& sdlRunner, ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>>& blockingQueue, bool& done);
    void play();
};


#endif //PORTAL_GAMECONTROLLER_H
