//
// Created by jonathanmedina on 05/06/19.
//

#ifndef SDL_SDL_RUNNER_H
#define SDL_SDL_RUNNER_H


#include "common/thread.h"
#include "common/SafeQueue.h"
#include "ComponentsSDL/Renderer.h"
#include "TextureFactory.h"

class SDL_Runner : public Thread{
    SafeQueue& safeQueue;
    bool connected;
    Window window;
    Renderer renderer;
    TextureFactory textureFactory;

public:
    SDL_Runner(std::string& title, SafeQueue& safeQueue);
    void run() override;
};


#endif //SDL_SDL_RUNNER_H
