//
// Created by jonathanmedina on 05/06/19.
//

#ifndef SDL_SDL_RUNNER_H
#define SDL_SDL_RUNNER_H


#include <Common/ProtectedBlockingQueue.h>
#include "ComponentsSDL/Renderer.h"
#include "TextureFactory.h"
#include "../Common/SafeQueue.h"
#include "../Common/Thread.h"

class SDL_Runner : public Thread{
    SafeQueue<std::shared_ptr<ProtocolDTO>>& safeQueue;
    bool& done;
    Window window;
    Renderer renderer;
    TextureFactory textureFactory;
    int16_t myChellId;

public:
    SDL_Runner(std::string& title, SafeQueue<std::shared_ptr<ProtocolDTO>>& safeQueue, bool& done);
    void run() override;
};


#endif //SDL_SDL_RUNNER_H
