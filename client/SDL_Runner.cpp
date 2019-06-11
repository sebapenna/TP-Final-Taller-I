//
// Created by jonathanmedina on 05/06/19.
//

#include <Common/ProtocolTranslator/ChellDTO.h>
#include <iostream>
#include <Common/ProtocolTranslator/PlayerChellIdDTO.h>
#include <client/View/DiagonalBlockMetalView.h>
#include <client/View/AcidView.h>
#include <client/View/RockView.h>
#include <Common/ProtocolTranslator/ButtonDTO.h>
#include <client/View/ButtonView.h>
#include <Common/ProtocolTranslator/ButtonStateDTO.h>
#include <Common/ProtocolTranslator/GateDTO.h>
#include <Common/ProtocolTranslator/GateStateDTO.h>
#include <Common/ProtocolTranslator/AcidDTO.h>
#include <Common/ProtocolTranslator/RockBlockDTO.h>
#include <Common/ProtocolTranslator/MetalBlockDTO.h>
#include <Common/ProtocolTranslator/MetalDiagonalBlockDTO.h>
#include <Common/ProtocolTranslator/RockDTO.h>
#include <Server/Model/constants.h>
#include <client/View/BackgroundView.h>
#include "SDL_Runner.h"
#include "ComponentsSDL/Window.h"
#include "ComponentsSDL/Renderer.h"
#include "View/ChellAnimationView.h"
#include "WorldView.h"
#include "client/View/BlockRockView.h"
#include "client/View/BlockMetalView.h"

SDL_Runner::SDL_Runner(std::string& title, SafeQueue<std::shared_ptr<ProtocolDTO>> &safeQueue, bool& done) :
safeQueue(safeQueue), done(done), window(title, 1000, 1000, SDL_WINDOW_SHOWN), renderer(window), textureFactory() {
    textureFactory.init(renderer);
    srand (time(NULL));
}

void SDL_Runner::run() {
    WorldView world;
    std::string chell_file_name("chell");
    std::string block_file_name("block");
    std::string bulletAndRock("bulletAndRock");
    std::string acidAndButtons("acidAndButtons");
    std::string gate_file_name("gate");
    std::string background("background");
    for (int startX = -2000; startX<7000; startX+=128) {
        /*for (int startY = -2000; startY<7000; startY+=128) {
            auto block = std::shared_ptr<BlockRockView>(new BlockRockView(textureFactory.getTextureByName(block_file_name), renderer));
            block->setDestRect(startX, startY, 128, 128);
            world.addView(block);
        }*/
        auto block = std::shared_ptr<BlockMetalView>(new BlockMetalView(textureFactory.getTextureByName(block_file_name), renderer));
        block->setDestRect(startX, 400, 128,128);
        world.addView(block);
    }
    auto acid = std::shared_ptr<AcidView>(new AcidView(textureFactory.getTextureByName(acidAndButtons),renderer));
    acid->setDestRect(192, 350, 128,50);
    world.addView(acid);


    int timeStepMs = 1000.f / 100.f;
    int timeLastMs = 0;
    int timeAccumulatedMs = 0;
    int timeCurrentMs = 0;
    while (!done) {
        renderer.clearRender();
        timeLastMs = timeCurrentMs;
        timeCurrentMs = SDL_GetTicks();
        int timeDeltaMs = timeCurrentMs - timeLastMs;
        timeAccumulatedMs += timeDeltaMs;

        while (timeAccumulatedMs >= timeStepMs) {
            auto aux = safeQueue.getTopAndPop();
            auto newItem = aux.get();
            if (newItem) {
                switch (newItem->getClassId()) {
                    case PROTOCOL_CHELL_DATA: {
                        auto newChell = (ChellDTO *) newItem;
                        auto chell2 = std::shared_ptr<ChellAnimationView>(new ChellAnimationView(newChell->getId(),
                                                             textureFactory.getTextureByName(chell_file_name), renderer));
                        Position chell2Pos(newChell->getX(), newChell->getY());
                        chell2.get()->setDestRect(newChell->getX(), newChell->getY(), newChell->getWidth(), newChell->getHeight());
                        world.addChell(chell2, chell2Pos);
                        if (newChell->getDeleteState() == DELETE) {
                            world.setChellState(newChell->getId(), ChellState::dying);
                        } else if (newChell->getMoving()) {
                            if (newChell->getDirection() == O_O) {
                                world.setChellState(newChell->getId(), ChellState::runningLeft);
                            } else {
                                world.setChellState(newChell->getId(), ChellState::runningRight);
                            }
                        } else if (newChell->getJumping() == JUMPING) {
                            world.setChellState(newChell->getId(), ChellState::flying);
                        } else {
                            world.setChellState(newChell->getId(), ChellState::standing);
                        }
                        if (newChell->getTilted() == NOT_TILTED) {
                            world.makeChellNotTilted(newChell->getId());
                        } else {
                            if (newChell->getTilted() == O_E) {
                                world.makeChellTiltedRight(newChell->getId());
                            } else if (newChell->getTilted() == O_O) {
                                world.makeChellTiltedLeft(newChell->getId());
                            }
                        }
                        break;
                    }
                    case PROTOCOL_PLAYER_CHELL_ID: {
                        auto chellId = (PlayerChellIdDTO*) newItem;
                        world.setCamara(chellId->getChellId(), 1000, 1000);
                        this->myChellId = chellId->getChellId();
                        auto back = std::shared_ptr<BackgroundView>(new BackgroundView(textureFactory.getTextureByName(background), renderer));
                        world.setBackground(back);
                        break;
                    }
                    case PROTOCOL_BUTTON_DATA: {
                        auto buttonData = (ButtonDTO*) newItem;
                        auto button = std::shared_ptr<ButtonView>(new ButtonView(buttonData->getId(), textureFactory.getTextureByName(acidAndButtons), renderer));
                        button.get()->setDestRect(buttonData->getX(), buttonData->getY(), buttonData->getWidth(), buttonData->getHeight());
                        world.addButton(button);
                        break;
                    }
                    case PROTOCOL_BUTTON_CHANGE_STATE: {
                        auto buttonState = (ButtonStateDTO*) newItem;
                        if (buttonState->getState() == PRESSED) {
                            world.activateButton(buttonState->getId());
                        } else {
                            world.deactivateButton(buttonState->getId());
                        }
                        break;
                    }
                    case PROTOCOL_GATE_DATA: {
                        auto gateDTO = (GateDTO*) newItem;
                        auto gate = std::shared_ptr<GateView>(new GateView(gateDTO->getId(), textureFactory.getTextureByName(gate_file_name), renderer));
                        gate.get()->setDestRect(gateDTO->getX(), gateDTO->getY(), gateDTO->getWidth(), gateDTO->getHeight());
                        world.addGates(gate);
                        break;
                    }
                    case PROTOCOL_GATE_CHANGE_STATE: {
                        auto gateState = (GateStateDTO*) newItem;
                        if (gateState->getState() == OPEN) {
                            world.openGate(gateState->getId());
                        } else {
                            world.closeGate(gateState->getId());
                        }
                        break;
                    }
                    case PROTOCOL_ACID_DATA: {
                        auto acidDTO = (AcidDTO*) newItem;
                        auto acid = std::shared_ptr<AcidView>(new AcidView(textureFactory.getTextureByName(acidAndButtons), renderer));
                        acid->setDestRect(acidDTO->getX(), acidDTO->getY(), acidDTO->getWidth(), acidDTO->getHeight());
                        world.addView(acid);
                        break;
                    }
                    case PROTOCOL_ROCK_BLOCK_DATA: {
                        auto rockBlockDTO = (RockBlockDTO*) newItem;
                        auto rockBlock = std::shared_ptr<BlockRockView>(new BlockRockView(textureFactory.getTextureByName(block_file_name), renderer));
                        rockBlock->setDestRect(rockBlockDTO->getX(), rockBlockDTO->getY(), rockBlockDTO->getWidth(), rockBlockDTO->getHeight());
                        world.addView(rockBlock);
                        break;
                    }
                    case PROTOCOL_METAL_BLOCK_DATA: {
                        auto metalBlockDTO = (MetalBlockDTO*) newItem;
                        auto metalBlock = std::shared_ptr<BlockMetalView>(new BlockMetalView(textureFactory.getTextureByName(block_file_name), renderer));
                        metalBlock->setDestRect(metalBlockDTO->getX(), metalBlockDTO->getY(), metalBlockDTO->getWidth(), metalBlockDTO->getHeight());
                        world.addView(metalBlock);
                        break;
                    }
                    case PROTOCOL_METAL_DIAGONAL_BLOCK_DATA: {
                        auto diagonalMetalBlockDTO = (MetalDiagonalBlockDTO*) newItem;
                        auto diagonalMetalBlock = std::shared_ptr<DiagonalBlockMetalView>(new DiagonalBlockMetalView(textureFactory.getTextureByName(block_file_name), renderer, diagonalMetalBlockDTO->getOrientation()));
                        diagonalMetalBlock->setDestRect(diagonalMetalBlockDTO->getX(), diagonalMetalBlockDTO->getY(), diagonalMetalBlockDTO->getSideLength(), diagonalMetalBlockDTO->getSideLength());
                        world.addView(diagonalMetalBlock);
                        break;
                    }
                    case PROTOCOL_ENERGY_TRANSMITTER_DATA: {
                        break;
                    }
                    case PROTOCOL_ENERGY_RECEIVER_DATA: {
                        break;
                    }
                    case PROTOCOL_ENERGY_BARRIER_DATA: {
                        break;
                    }
                    case PROTOCOL_ROCK_DATA: {
                        auto rockDTO = (RockDTO*)newItem;
                        auto rock = std::shared_ptr<RockView>(new RockView(rockDTO->getId(), textureFactory.getTextureByName(bulletAndRock), renderer));
                        rock->setDestRect(rockDTO->getX(), rockDTO->getY(), rockDTO->getSideLength(), rockDTO->getSideLength());
                        world.addRock(rock);
                        break;
                    }
                    case PROTOCOL_ENERGY_BALL_DATA: {
                        break;
                    }
                    case PROTOCOL_PORTAL_DATA: {
                        break;
                    }
                    case PROTOCOL_PIN_TOOL_DATA: {
                        break;
                    }
                    case PROTOCOL_ENERGY_TRANSMITTER_ACTIVATE: {
                        break;
                    }
                    case PROTOCOL_ENERGY_RECEIVER_ACTIVATE: {
                        break;
                    }
                    
                }
            }
            world.draw();
            timeAccumulatedMs -= timeStepMs;
        }
        renderer.render();
    }
}
