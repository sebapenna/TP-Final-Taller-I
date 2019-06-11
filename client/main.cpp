#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <exception>
#include "ComponentsSDL/Window.h"
#include "ComponentsSDL/Renderer.h"
#include "View/ChellAnimationView.h"
#include "TextureFactory.h"
#include "WorldView.h"
#include "client/View/BlockMetalView.h"
#include "client/View/BlockRockView.h"
#include <queue>
#include <Common/ProtocolTranslator/JumpDTO.h>
#include <Common/ProtocolTranslator/StopDTO.h>
#include <Common/Protocol.h>
#include <Common/ProtocolTranslator/ConnectionDTO/BeginDTO.h>
#include <Common/ProtocolTranslator/ConnectionDTO/QuitDTO.h>
#include "SDL_Runner.h"
#include "FakeServer.h"
#include "../Common/ProtocolTranslator/MoveLeftDTO.h"
#include "../Common/ProtocolTranslator/MoveRightDTO.h"
#include "../Common/SafeQueue.h"
#include "ClientSender.h"
#include "ClientReceiver.h"


int main(int argc, char** argv){
    try {
        // Chell turning around
        //AnimatedSprite sprite("chell.png", renderer, 292, 209, 1, 3753, 8, 8, 0, 0, 292, 209, 1, 0);
        std::string title("Portal");
        bool done = false;

        ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>> blockingQueue;
        SafeQueue<std::shared_ptr<ProtocolDTO>> safeQueue;

        SDL_Runner sdlRunner(title, safeQueue, done);
        sdlRunner.start();
        Protocol protocol("localhost", "8080");

        ClientSender clientSender(protocol, blockingQueue, done);
        clientSender.run();

        ClientReceiver clientReceiver(protocol, safeQueue, done);
        clientReceiver.run();
       /* FakeServer server(blockingQueue, safeQueue, done);
        server.start();*/

        SDL_Event e;
        std::shared_ptr<ProtocolDTO> beginDTO (new BeginDTO());
        blockingQueue.push(beginDTO);
        while (!done) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    done=true;
                    break;
                } else if (e.type == SDL_MOUSEBUTTONDOWN){
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        //chell.fire();
                    }
                } else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_d: {
                            std::shared_ptr<ProtocolDTO> dto (new MoveRightDTO());
                            blockingQueue.push(dto);
                            break;
                        }
                        case SDLK_a: {
                            std::shared_ptr<ProtocolDTO> dto (new MoveLeftDTO());
                            blockingQueue.push(dto);
                            break;
                        }
                        case SDLK_w: {
                            std::shared_ptr<ProtocolDTO>dto(new JumpDTO());
                            blockingQueue.push(dto);
                            break;
                        }
                        case SDLK_q: {
                            std::shared_ptr<ProtocolDTO>dto(new QuitDTO());
                            blockingQueue.push(dto);
                            done=true;
                            break;
                        }

                    }
                } else if (e.type == SDL_KEYUP) {
                    std::shared_ptr<ProtocolDTO> dto (new StopDTO());
                    blockingQueue.push(dto);
                }
            }
        }
        sdlRunner.join();
        blockingQueue.setFinishedAdding();
        clientSender.join();
        clientReceiver.join();
        //server.join();
        return 0;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
