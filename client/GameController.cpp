//
// Created by jonathanmedina on 24/06/19.
//
#include <SDL2/SDL.h>
#include "GameController.h"
#include "Common/ProtocolTranslator/PlayerActionsDTO/MoveLeftDTO.h"
#include "Common/ProtocolTranslator/PlayerActionsDTO/MoveRightDTO.h"
#include <Common/ProtocolTranslator/PlayerActionsDTO/JumpDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/StopDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/CommitSuicideDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/KillMissingChellDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/LiftRockDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/DropRockDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/ShootPortalDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/ShootPinToolDTO.h>
#include <Common/ProtocolTranslator/ResetPortalsDTO.h>
#include <Common/ProtocolTranslator/GameStateDTO/QuitDTO.h>

GameController::GameController(SDL_Runner &sdlRunner,
                               ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>> &blockingQueue, bool &done) :
                               sdlRunner(sdlRunner), blockingQueue(blockingQueue), done(done) {
}

void GameController::positionInScreen(int& x, int& y, SDL_Runner& sdlRunner) {
    int x_m;
    int y_m;
    SDL_GetMouseState(&x_m, &y_m);
    sdlRunner.getRealPos(x, y, x_m, y_m);
}

void GameController::play() {
    std::setlocale(LC_NUMERIC, "C");
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
                    int x;
                    int y;
                    positionInScreen(x, y, sdlRunner);
                    std::shared_ptr<ProtocolDTO> dto(new ShootPortalDTO(BLUE_PORTAL, x, y));
                    blockingQueue.push(dto);
                } else if (e.button.button == SDL_BUTTON_RIGHT) {
                    int x;
                    int y;
                    positionInScreen(x, y, sdlRunner);

                    std::shared_ptr<ProtocolDTO> dto(new ShootPortalDTO(ORANGE_PORTAL, x, y));
                    blockingQueue.push(dto);
                } else if (e.button.button == SDL_BUTTON_MIDDLE) {
                    int x;
                    int y;
                    positionInScreen(x, y, sdlRunner);

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
                    case SDLK_r: {
                        std::shared_ptr<ProtocolDTO> dto(new ResetPortalsDTO());
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

}
