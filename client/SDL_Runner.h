//
// Created by jonathanmedina on 05/06/19.
//

#ifndef SDL_SDL_RUNNER_H
#define SDL_SDL_RUNNER_H


#include <Common/ProtectedBlockingQueue.h>
#include <Common/ProtocolTranslator/DataDTO/PlayerChellIdDTO.h>
#include <Common/ProtocolTranslator/DataDTO/ButtonDTO.h>
#include "ComponentsSDL/Renderer.h"
#include "TextureFactory.h"
#include "../Common/SafeQueue.h"
#include "../Common/Thread.h"
#include "WorldView.h"

class SDL_Runner : public Thread {
private:
    SafeQueue<std::shared_ptr<ProtocolDTO>>& safeQueue;
    bool& done;
    Window window;
    Renderer renderer;
    TextureFactory textureFactory;
    WorldView world;
    int16_t myChellId;

    void addButton(ButtonDTO* buttonData, std::string& file_name);
    void addPlayerId(PlayerChellIdDTO* chellId, std::string& file_name);
public:
    SDL_Runner(std::string& title, SafeQueue<std::shared_ptr<ProtocolDTO>>& safeQueue, bool& done);
    void getRealPos(int& x, int& y, int x_m, int y_m);
    void run() override;
};


#endif //SDL_SDL_RUNNER_H
