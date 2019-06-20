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
#include <Common/ProtocolTranslator/PlayerActionsDTO/JumpDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/StopDTO.h>
#include <Common/Protocol.h>
#include <Common/ProtocolTranslator/GameStateDTO/BeginDTO.h>
#include <Common/ProtocolTranslator/GameStateDTO/QuitDTO.h>
#include <zconf.h>
#include <Common/HandshakeHandler.h>
#include <Common/exceptions.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/CommitSuicideDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/KillMissingChellDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/LiftRockDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/DropRockDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/ShootPortalDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/ShootPinToolDTO.h>
#include "SDL_Runner.h"
#include "FakeServer.h"
#include "Common/ProtocolTranslator/PlayerActionsDTO/MoveLeftDTO.h"
#include "Common/ProtocolTranslator/PlayerActionsDTO/MoveRightDTO.h"
#include "../Common/SafeQueue.h"
#include "ClientSender.h"
#include "ClientReceiver.h"
#include "CommandReceiver.h"
#include "CommandSender.h"

#define KNOWN_ERROR 1
#define UNKNOWN_ERROR 2
#define DELAY 1
int main(int argc, char** argv){
    try {
        // Chell turning around
        //AnimatedSprite sprite("chell.png", renderer, 292, 209, 1, 3753, 8, 8, 0, 0, 292, 209, 1, 0);
        std::string title("Portal");
        /*Protocol protocol("localhost", argv[1]);

        HandshakeHandler::getOptionsAndChoose(protocol); // Obtengo mensajes de bienvenidas, opciones, etc
        // Tirar dos threads, uno que lea la entrada, y otro que espere a lo que le responde el server.
        // Luego ejecuto como antes..
        bool done_with_start = false;
        bool user_quit_game = false;

        CommandReceiver commandReceiver(protocol, done_with_start, user_quit_game);
        commandReceiver.start();

        CommandSender commandSender(protocol, done_with_start, user_quit_game);
        commandSender.start();

        commandReceiver.join();
        commandSender.join();

        if (user_quit_game) return 1;*/

        bool done = false;
        ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>> blockingQueue;
        SafeQueue<std::shared_ptr<ProtocolDTO>> safeQueue;

        /*ClientSender clientSender(protocol, blockingQueue, done);
        clientSender.start();

        ClientReceiver clientReceiver(protocol, safeQueue, done);
        clientReceiver.start();*/
        SDL_Runner sdlRunner(title, safeQueue, done);
        sdlRunner.start();


        FakeServer server(blockingQueue, safeQueue, done);
        server.start();

        SDL_Event e;
        while (!done) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    std::shared_ptr<ProtocolDTO> dto(new QuitDTO());
                    blockingQueue.push(dto);
                    done = true;
                    break;
                } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        int x_m;
                        int y_m;
                        SDL_GetMouseState(&x_m, &y_m);

                        int x;
                        int y;
                        sdlRunner.getRealPos(x, y, x_m, y_m);
                        std::shared_ptr<ProtocolDTO> dto(new ShootPortalDTO(BLUE_PORTAL, x, y));
                        blockingQueue.push(dto);
                    } else if (e.button.button == SDL_BUTTON_RIGHT) {
                        int x_m;
                        int y_m;
                        SDL_GetMouseState(&x_m, &y_m);

                        int x;
                        int y;
                        sdlRunner.getRealPos(x, y, x_m, y_m);
                        std::shared_ptr<ProtocolDTO> dto(new ShootPortalDTO(ORANGE_PORTAL, x, y));
                        blockingQueue.push(dto);
                    } else if (e.button.button == SDL_BUTTON_MIDDLE) {
                        int x_m;
                        int y_m;
                        SDL_GetMouseState(&x_m, &y_m);

                        int x;
                        int y;
                        sdlRunner.getRealPos(x, y, x_m, y_m);
                        std::shared_ptr<ProtocolDTO> dto(new ShootPinToolDTO(x, y));
                        blockingQueue.push(dto);
                    }
                } else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_d: {
                            std::shared_ptr<ProtocolDTO> dto(new MoveRightDTO());
                            blockingQueue.push(dto);
                            break;
                        }
                        case SDLK_a: {
                            std::shared_ptr<ProtocolDTO> dto(new MoveLeftDTO());
                            blockingQueue.push(dto);
                            break;
                        }
                        case SDLK_w: {
                            std::shared_ptr<ProtocolDTO> dto(new JumpDTO());
                            blockingQueue.push(dto);
                            break;
                        }
                        case SDLK_q: {
                            std::shared_ptr<ProtocolDTO> dto(new QuitDTO());
                            blockingQueue.push(dto);
                            done = true;
                            break;
                        }
                        case SDLK_o: {
                            std::shared_ptr<ProtocolDTO> dto(new CommitSuicideDTO());
                            blockingQueue.push(dto);
                            break;
                        }
                        case SDLK_k: {
                            std::shared_ptr<ProtocolDTO> dto(new KillMissingChellDTO());
                            blockingQueue.push(dto);
                            break;
                        }
                        case SDLK_e: {
                            std::shared_ptr<ProtocolDTO> dto(new LiftRockDTO(0));
                            blockingQueue.push(dto);
                            break;
                        }
                        case SDLK_f: {
                            std::shared_ptr<ProtocolDTO> dto(new DropRockDTO());
                            blockingQueue.push(dto);
                            break;
                        }

                    }
                } else if (e.type == SDL_KEYUP) {
                    std::shared_ptr<ProtocolDTO> dto(new StopDTO());
                    blockingQueue.push(dto);
                }
            }
            SDL_Delay(1);
        }
        /*protocol.disconnect();*/
        sdlRunner.join();
        /*blockingQueue.setFinishedAdding();

        clientSender.join();
        clientReceiver.join();*/

        server.join();
        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return KNOWN_ERROR;
    }  catch(...) {
        std::cout << UnknownException().what();
        return UNKNOWN_ERROR;
    }
}
