//
// Created by jonathanmedina on 05/06/19.
//

#include <Common/ProtocolTranslator/DataDTO/ChellDTO.h>
#include <iostream>
#include <Common/ProtocolTranslator/DataDTO/PlayerChellIdDTO.h>
#include <client/View/DiagonalBlockMetalView.h>
#include <client/View/AcidView.h>
#include <client/View/RockView.h>
#include <Common/ProtocolTranslator/DataDTO/ButtonDTO.h>
#include <client/View/ButtonView.h>
#include <Common/ProtocolTranslator/DataDTO/ButtonStateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/GateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/GateStateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/AcidDTO.h>
#include <Common/ProtocolTranslator/DataDTO/RockBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/MetalBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/MetalDiagonalBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/RockDTO.h>
#include <Server/Model/constants.h>
#include <client/View/BackgroundView.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyBarrierDTO.h>
#include <client/View/EnergyBarrierView.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyReceiverDTO.h>
#include <client/View/EnergyReceiverView.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyReceiverActivateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/CakeDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyTransmitterDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyTransmitterActivateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyBallDTO.h>
#include "SDL_Runner.h"
#include "ComponentsSDL/Window.h"
#include "ComponentsSDL/Renderer.h"
#include "View/ChellAnimationView.h"
#include "WorldView.h"
#include "client/View/BlockRockView.h"
#include "client/View/BlockMetalView.h"


#define CUT_LEN_BLOCKS 4

SDL_Runner::SDL_Runner(std::string& title, SafeQueue<std::shared_ptr<ProtocolDTO>> &safeQueue, bool& done) :
safeQueue(safeQueue), done(done), window(title, 1600, 1000, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE), renderer(window), textureFactory() {
    textureFactory.init(renderer);
    srand (time(NULL));
}

void SDL_Runner::run() {
    WorldView world;
    std::string chell_file_name("chell");
    std::string block_file_name("block");
    std::string bulletAndRock_filename("bulletAndRock");
    std::string acidAndButtons_filename("acidAndButtons");
    std::string gate_file_name("gate");
    std::string cake_file_name("cake");
    std::string background("background");
    bool done_receiving = false;
    while (!done_receiving) {
        auto aux = safeQueue.getTopAndPop();
        auto newItem = aux.get();
        if (newItem) {
            switch (newItem->getClassId()) {
                case PROTOCOL_BEGIN: {
                    done_receiving = true;
                    break;
                }
                case PROTOCOL_CHELL_DATA: {
                    auto newChell = (ChellDTO *) newItem;
                    auto chell2 =
                            std::shared_ptr<ChellAnimationView>(new ChellAnimationView(newChell->getId(),
                                    textureFactory.getTextureByName(chell_file_name), renderer));
                    chell2->setDestRect(newChell->getX(), newChell->getY(), newChell->getWidth(),
                                        newChell->getHeight());
                    world.addChell(chell2);
                    break;
                }
                case PROTOCOL_PLAYER_CHELL_ID: {
                    auto chellId = (PlayerChellIdDTO *) newItem;
                    world.setCamara(chellId->getChellId(), window.getWidth(), window.getHeight());
                    this->myChellId = chellId->getChellId();
                    auto back = std::shared_ptr<BackgroundView>(
                            new BackgroundView(textureFactory.getTextureByName(background), renderer));
                    world.setBackground(back);
                    break;
                }
                case PROTOCOL_BUTTON_DATA: {
                    auto buttonData = (ButtonDTO *) newItem;
                    auto button = std::shared_ptr<ButtonView>(
                            new ButtonView(buttonData->getId(), textureFactory.getTextureByName(acidAndButtons_filename),
                                           renderer));
                    button.get()->setDestRect(buttonData->getX(), buttonData->getY(), buttonData->getWidth(),
                                              buttonData->getHeight());
                    world.addButton(button);
                    break;
                }
                case PROTOCOL_GATE_DATA: {
                    auto gateDTO = (GateDTO*) newItem;
                    auto gate = std::shared_ptr<GateView>(new GateView(gateDTO->getId(), textureFactory.getTextureByName(gate_file_name), renderer));
                    gate.get()->setDestRect(gateDTO->getX(), gateDTO->getY(), gateDTO->getWidth(), gateDTO->getHeight());
                    world.addGates(gate);
                    break;
                }
                case PROTOCOL_ACID_DATA: {
                    auto acidDTO = (AcidDTO*) newItem;
                    auto acid = std::shared_ptr<AcidView>(new AcidView(textureFactory.getTextureByName(acidAndButtons_filename), renderer));
                    acid->setDestRect(acidDTO->getX(), acidDTO->getY(), acidDTO->getWidth(), acidDTO->getHeight());
                    world.addView(acid);
                    break;
                }
                case PROTOCOL_ROCK_BLOCK_DATA: {
                    auto rockBlockDTO = (RockBlockDTO*) newItem;
                    for(int i=0; i<rockBlockDTO->getWidth(); i+=CUT_LEN_BLOCKS) {
                        for (int j = 0; j<rockBlockDTO->getHeight(); j+=CUT_LEN_BLOCKS) {
                            auto rockBlock = std::shared_ptr<BlockRockView>(new BlockRockView(textureFactory.getTextureByName(block_file_name), renderer));
                            rockBlock->setDestRect(rockBlockDTO->getX()+i, rockBlockDTO->getY()+j, CUT_LEN_BLOCKS, CUT_LEN_BLOCKS);
                            world.addView(rockBlock);    
                        }
                    }
                    break;
                }
                case PROTOCOL_METAL_BLOCK_DATA: {
                    auto metalBlockDTO = (MetalBlockDTO*) newItem;
                    for(int i=0; i<metalBlockDTO->getWidth(); i+=CUT_LEN_BLOCKS) {
                        for (int j = 0; j<metalBlockDTO->getHeight(); j+=CUT_LEN_BLOCKS) {
                            auto metalBlock = std::shared_ptr<BlockMetalView>(new BlockMetalView(textureFactory.getTextureByName(block_file_name), renderer));
                            metalBlock->setDestRect(metalBlockDTO->getX()+i, metalBlockDTO->getY() + j, CUT_LEN_BLOCKS, CUT_LEN_BLOCKS);
                            world.addView(metalBlock);
                        }
                    }
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
                    auto energyTransmitterDTO = (EnergyTransmitterDTO*) newItem;
                    auto energyTransmitter = std::shared_ptr<EnergyTransmitterView>(new EnergyTransmitterView(energyTransmitterDTO->getId(), textureFactory.getTextureByName(block_file_name), renderer, energyTransmitterDTO->getDirection()));
                    energyTransmitter->setDestRect(energyTransmitterDTO->getX(), energyTransmitterDTO->getY(), energyTransmitterDTO->getSideLength(), energyTransmitterDTO->getSideLength());
                    world.addTransmitter(energyTransmitter);
                    break;
                }
                case PROTOCOL_ENERGY_RECEIVER_DATA: {
                    auto energyReceiverDTO = (EnergyReceiverDTO*) newItem;
                    auto energyReceiver = std::shared_ptr<EnergyReceiverView>(new EnergyReceiverView(energyReceiverDTO->getId(), textureFactory.getTextureByName(block_file_name), renderer));
                    energyReceiver->setDestRect(energyReceiverDTO->getX(), energyReceiverDTO->getY(), energyReceiverDTO->getSideLength(), energyReceiverDTO->getSideLength());
                    world.addReceiver(energyReceiver);
                    break;
                }
                case PROTOCOL_ENERGY_BARRIER_DATA: {
                    auto energyBarrierDTO = (EnergyBarrierDTO*) newItem;
                    auto energyBarrier = std::shared_ptr<EnergyBarrierView>(new EnergyBarrierView(textureFactory.getTextureByName(acidAndButtons_filename), renderer));
                    energyBarrier->setDestRect(energyBarrierDTO->getX(), energyBarrierDTO->getY(), energyBarrierDTO->getWidth(), energyBarrierDTO->getHeight());
                    world.addView(energyBarrier);
                    break;
                }
                case PROTOCOL_ROCK_DATA: {
                    auto rockDTO = (RockDTO*) newItem;
                    auto rock = std::shared_ptr<RockView>(new RockView(rockDTO->getId(), textureFactory.getTextureByName(bulletAndRock_filename), renderer));
                    rock->setDestRect(rockDTO->getX(), rockDTO->getY(), rockDTO->getSideLength(), rockDTO->getSideLength());
                    world.addRock(rock);
                    break;
                }
                case PROTOCOL_CAKE_DATA: {
                    auto cakeDTO = (CakeDTO*) newItem;
                    auto cake = std::shared_ptr<CakeView>(new CakeView(textureFactory.getTextureByName(cake_file_name), renderer));
                    cake->setDestRect(cakeDTO->getX(), cakeDTO->getY(), cakeDTO->getSideLength(), cakeDTO->getSideLength());
                    world.addCake(cake);
                    break;
                }
            }
        }
    }

    int timeStepMs = 1000.f / 80.f;
    int timeLastMs = 0;
    int timeAccumulatedMs = 0;
    int timeCurrentMs = 0;
    while (!done) {
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
                        if (newChell->getDeleteState() == DELETE) {
                            world.setChellState(newChell->getId(), ChellState::dying);
                            continue;
                        } else {
                            chell2->setDestRect(newChell->getX(), newChell->getY(), newChell->getWidth(), newChell->getHeight());
                            world.addChell(chell2);
                        }
                        if (newChell->getJumping() == JUMPING) {
                            world.setChellState(newChell->getId(), ChellState::flying);
                        } else if (newChell->getMoving()) {
                            if (newChell->getDirection() == O_O) {
                                world.setChellState(newChell->getId(), ChellState::runningLeft);
                            } else {
                                world.setChellState(newChell->getId(), ChellState::runningRight);
                            }
                        } else if (newChell->getShooting() == SHOOTING) {
                            world.setChellState(newChell->getId(), ChellState::firing);
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
                    case PROTOCOL_BUTTON_CHANGE_STATE: {
                        auto buttonState = (ButtonStateDTO*) newItem;
                        if (buttonState->getState() == PRESSED) {
                            world.activateButton(buttonState->getId());
                        } else {
                            world.deactivateButton(buttonState->getId());
                        }
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
                    case PROTOCOL_ROCK_DATA: {
                        auto rockDTO = (RockDTO*)newItem;
                        if (rockDTO->getDeleteState() == DELETE) {
                            world.removeRock(rockDTO->getId());
                        } else {
                            auto rock = std::shared_ptr<RockView>(new RockView(rockDTO->getId(), textureFactory.getTextureByName(bulletAndRock_filename), renderer));
                            rock->setDestRect(rockDTO->getX(), rockDTO->getY(), rockDTO->getSideLength(), rockDTO->getSideLength());
                            world.addRock(rock);
                        }
                        break;
                    }
                    case PROTOCOL_ENERGY_BALL_DATA: {
                        auto energyBallDTO = (EnergyBallDTO*) newItem;
                        if (energyBallDTO->getDeleteState() == DELETE) {
                            world.removeBall(energyBallDTO->getId());
                        } else {
                            auto ball = std::shared_ptr<EnergyBallView>(new EnergyBallView(energyBallDTO->getId(), textureFactory.getTextureByName(bulletAndRock_filename), renderer));
                            ball->setDestRect(energyBallDTO->getX(), energyBallDTO->getY(), energyBallDTO->getRadius());
                            world.addBall(ball);
                        }
                        break;
                    }
                    case PROTOCOL_PORTAL_DATA: {
                        break;
                    }
                    case PROTOCOL_PIN_TOOL_DATA: {
                        break;
                    }
                    case PROTOCOL_ENERGY_TRANSMITTER_ACTIVATE: {
                        auto energyTransmitterActivateDTO = (EnergyTransmitterActivateDTO*) newItem;
                        world.activateTransmitter(energyTransmitterActivateDTO->getId());
                        break;
                    }
                    case PROTOCOL_ENERGY_RECEIVER_ACTIVATE: {
                        auto energyReceiverActivateDTO = (EnergyReceiverActivateDTO*)newItem;
                        world.activateReceiver(energyReceiverActivateDTO->getId());
                        break;
                    }
                }
            }
            timeAccumulatedMs -= timeStepMs;
        }
        renderer.clearRender();
        world.draw();
        renderer.render();
        //SDL_Delay(5);
    }
}
