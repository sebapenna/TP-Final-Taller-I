//
// Created by jonathanmedina on 05/06/19.
//

#include <iostream>
#include <client/View/DiagonalBlockMetalView.h>
#include <client/View/AcidView.h>
#include <client/View/RockView.h>
#include <client/View/ButtonView.h>
#include <Server/Model/constants.h>
#include <client/View/BackgroundView.h>
#include <client/View/EnergyBarrierView.h>
#include <client/View/EnergyReceiverView.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyTransmitterActivateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyReceiverActivateDTO.h>
#include "SDL_Runner.h"
#include "ComponentsSDL/Window.h"
#include "ComponentsSDL/Renderer.h"
#include "View/ChellAnimationView.h"
#include "WorldView.h"
#include "client/View/BlockRockView.h"
#include "client/View/BlockMetalView.h"


#define CUT_LEN_BLOCKS 4
#define DELAY 2

SDL_Runner::SDL_Runner(std::string& title, SafeQueue<std::shared_ptr<ProtocolDTO>> &safeQueue, bool& done) :
    safeQueue(safeQueue), done(done), window(title, 1600, 1000, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE),
    renderer(window), textureFactory(), soundFactory(), musicPlayer(soundFactory) {
    textureFactory.init(renderer);
    srand(time(NULL));
}

void SDL_Runner::addChell(ChellDTO *chellDTO) {
    auto chell2 = std::make_shared<ChellAnimationView>(chellDTO->getId(), textureFactory.getChellTexture(), renderer);
    if (chellDTO->getDeleteState() == DELETE) {
        world.setChellState(chellDTO->getId(), ChellState::dying);
        if (myChellId == chellDTO->getId()) {
            musicPlayer.playLoserSong();
        }
        return;
    } else {
        chell2->setDestRect(chellDTO->getX(), chellDTO->getY(), chellDTO->getWidth(), chellDTO->getHeight());
        world.addChell(chell2);
    }
    if (chellDTO->getJumping() == JUMPING) {
        if (world.getChellState(chellDTO->getId()) != ChellState::flying) {
            musicPlayer.playPlayerJumping();
        }
        world.setChellState(chellDTO->getId(), ChellState::flying);
    } else if (chellDTO->getMoving()) {
        if (chellDTO->getDirection() == O_O) {
            world.setChellState(chellDTO->getId(), ChellState::runningLeft);
        } else {
            world.setChellState(chellDTO->getId(), ChellState::runningRight);
        }
    } else if (chellDTO->getShooting() == SHOOTING) {
        musicPlayer.playPlayerFiring();
        world.setChellState(chellDTO->getId(), ChellState::firing);
    } else {
        world.setChellState(chellDTO->getId(), ChellState::standing);
    }
    if (chellDTO->getTilted() == NOT_TILTED) {
        world.makeChellNotTilted(chellDTO->getId());
    } else {
        if (chellDTO->getTilted() == O_E) {
            world.makeChellTiltedRight(chellDTO->getId());
        } else if (chellDTO->getTilted() == O_O) {
            world.makeChellTiltedLeft(chellDTO->getId());
        }
    }
}

void SDL_Runner::addPlayerId(PlayerChellIdDTO* chellId) {
    world.setCamara(chellId->getChellId(), window.getWidth(), window.getHeight());
    this->myChellId = chellId->getChellId();
    auto back = std::make_shared<BackgroundView>(textureFactory.getBackground(), renderer);
    world.setBackground(back);
}

void SDL_Runner::addButton(ButtonDTO* buttonData) {
    auto button = std::make_shared<ButtonView>(buttonData->getId(),
            textureFactory.getAcidAndButtonsTexture(), renderer);
    button.get()->setDestRect(buttonData->getX(), buttonData->getY(), buttonData->getWidth(),
                              buttonData->getHeight());
    world.addButton(button);
}

void SDL_Runner::addGate(GateDTO *gateDTO) {
    auto gate = std::make_shared<GateView>(gateDTO->getId(), textureFactory.getGateTexture(), renderer);
    gate.get()->setDestRect(gateDTO->getX(), gateDTO->getY(), gateDTO->getWidth(), gateDTO->getHeight());
    world.addGates(gate);
}

void SDL_Runner::addAcid(AcidDTO *acidDTO) {
    auto acid = std::make_shared<AcidView>(textureFactory.getAcidAndButtonsTexture(), renderer);
    acid->setDestRect(acidDTO->getX(), acidDTO->getY(), acidDTO->getWidth(), acidDTO->getHeight());
    world.addView(acid);
}

void SDL_Runner::addRockBlock(RockBlockDTO *rockBlockDTO) {
    for(int i=0; i<rockBlockDTO->getWidth(); i+=CUT_LEN_BLOCKS) {
        for (int j = 0; j<rockBlockDTO->getHeight(); j+=CUT_LEN_BLOCKS) {
            auto rockBlock = std::make_shared<BlockRockView>(textureFactory.getBlockTexture(), renderer);
            int width = i+CUT_LEN_BLOCKS>rockBlockDTO->getWidth()? rockBlockDTO->getWidth() - i : CUT_LEN_BLOCKS;
            int height = j+CUT_LEN_BLOCKS>rockBlockDTO->getHeight()? rockBlockDTO->getHeight() - j : CUT_LEN_BLOCKS;
            rockBlock->setDestRect(rockBlockDTO->getX()+i, rockBlockDTO->getY()+j, width, height);
            world.addView(rockBlock);
        }
    }
}

void SDL_Runner::addMetalBlock(MetalBlockDTO *metalBlockDTO) {
    for(int i=0; i<metalBlockDTO->getWidth(); i+=CUT_LEN_BLOCKS) {
        for (int j = 0; j<metalBlockDTO->getHeight(); j+=CUT_LEN_BLOCKS) {
            auto metalBlock = std::make_shared<BlockMetalView>(textureFactory.getBlockTexture(), renderer);
            int width = i+CUT_LEN_BLOCKS>metalBlockDTO->getWidth()? metalBlockDTO->getWidth() - i : CUT_LEN_BLOCKS;
            int height = j+CUT_LEN_BLOCKS>metalBlockDTO->getHeight()? metalBlockDTO->getHeight() - j : CUT_LEN_BLOCKS;
            metalBlock->setDestRect(metalBlockDTO->getX()+i, metalBlockDTO->getY() + j, width, height);
            world.addView(metalBlock);
        }
    }
}

void SDL_Runner::addMetalDiagonalBlock(MetalDiagonalBlockDTO *metalDiagonalBlockDTO) {
    auto diagonalMetalBlock = std::make_shared<DiagonalBlockMetalView>(textureFactory.getBlockTexture(), renderer, metalDiagonalBlockDTO->getOrientation());
    diagonalMetalBlock->setDestRect(metalDiagonalBlockDTO->getX(), metalDiagonalBlockDTO->getY(), metalDiagonalBlockDTO->getSideLength(), metalDiagonalBlockDTO->getSideLength());
    world.addView(diagonalMetalBlock);
}

void SDL_Runner::addEnergyTransmitter(EnergyTransmitterDTO *energyTransmitterDTO) {
    auto energyTransmitter = std::make_shared<EnergyTransmitterView>(energyTransmitterDTO->getId(), textureFactory.getBlockTexture(), renderer, energyTransmitterDTO->getDirection());
    energyTransmitter->setDestRect(energyTransmitterDTO->getX(), energyTransmitterDTO->getY(), energyTransmitterDTO->getSideLength(), energyTransmitterDTO->getSideLength());
    world.addTransmitter(energyTransmitter);
}

void SDL_Runner::addEnergyReceiver(EnergyReceiverDTO *energyReceiverDTO) {
    auto energyReceiver = std::make_shared<EnergyReceiverView>(energyReceiverDTO->getId(), textureFactory.getBlockTexture(), renderer);
    energyReceiver->setDestRect(energyReceiverDTO->getX(), energyReceiverDTO->getY(), energyReceiverDTO->getSideLength(), energyReceiverDTO->getSideLength());
    world.addReceiver(energyReceiver);
}

void SDL_Runner::addEnergyBarrier(EnergyBarrierDTO *energyBarrierDTO) {
    auto energyBarrier = std::make_shared<EnergyBarrierView>(textureFactory.getAcidAndButtonsTexture(), renderer);
    energyBarrier->setDestRect(energyBarrierDTO->getX(), energyBarrierDTO->getY(), energyBarrierDTO->getWidth(), energyBarrierDTO->getHeight());
    world.addView(energyBarrier);
}

void SDL_Runner::addRock(RockDTO *rockDTO) {
    if (rockDTO->getDeleteState() == DELETE) {
        world.removeRock(rockDTO->getId());
    } else {
        auto rock = std::make_shared<RockView>(rockDTO->getId(), textureFactory.getBulletAndRocksTexture(), renderer);
        rock->setDestRect(rockDTO->getX(), rockDTO->getY(), rockDTO->getSideLength(), rockDTO->getSideLength());
        world.addRock(rock);
    }
}

void SDL_Runner::addCake(CakeDTO *cakeDTO) {
    auto cake = std::make_shared<CakeView>(textureFactory.getCakeTexture(), renderer);
    cake->setDestRect(cakeDTO->getX(), cakeDTO->getY(), cakeDTO->getSideLength(), cakeDTO->getSideLength());
    world.addCake(cake);
}

void SDL_Runner::setButtonState(ButtonStateDTO *buttonStateDTO) {
    if (buttonStateDTO->getState() == PRESSED) {
        this->musicPlayer.playButtonPress();
        world.activateButton(buttonStateDTO->getId());
    } else {
        this->musicPlayer.playButtonUnpress();
        world.deactivateButton(buttonStateDTO->getId());
    }
}

void SDL_Runner::setGateState(GateStateDTO *gateStateDTO) {
    if (gateStateDTO->getState() == OPEN) {
        musicPlayer.playGateOpening();
        world.openGate(gateStateDTO->getId());
    } else {
        musicPlayer.playGateClosing();
        world.closeGate(gateStateDTO->getId());
    }
}

void SDL_Runner::addEnergyBall(EnergyBallDTO *energyBallDTO) {
    if (energyBallDTO->getDeleteState() == DELETE) {
        world.removeBall(energyBallDTO->getId());
    } else {
        auto ball = std::make_shared<EnergyBallView>(energyBallDTO->getId(), textureFactory.getBulletAndRocksTexture(), renderer);
        ball->setDestRect(energyBallDTO->getX(), energyBallDTO->getY(), energyBallDTO->getRadius());
        world.addBall(ball);
    }
}

void SDL_Runner::addPortal(PortalDTO *portalDTO) {
    if (portalDTO->getDeleteState() == DELETE) {
        world.removePortal(portalDTO->getId());
    } else {
        std::shared_ptr<View> portal;
        if (portalDTO->getColour() == BLUE_PORTAL) {
            portal = std::make_shared<PortalBlueView>(textureFactory.getPortalTexture(), renderer, portalDTO->getTilt());
        } else {
            portal = std::make_shared<PortalOrangeView>(textureFactory.getPortalTexture(), renderer, portalDTO->getTilt());
        }
        portal->setDestRect(portalDTO->getX(), portalDTO->getY(), portalDTO->getWidth(), portalDTO->getHeight());
        world.addPortal(portalDTO->getId(), portal);
    }
}

void SDL_Runner::addPinTool(PinToolDTO *pinToolDTO) {
    if (pinToolDTO->getDeleteState() == DELETE) {
        world.removePinTool(pinToolDTO->getId());
    } else {
        auto pinTool = std::make_shared<PinToolView>(pinToolDTO->getId(), textureFactory.getPintoolTexture(), renderer);
        pinTool->setDestRect(pinToolDTO->getX(), pinToolDTO->getY(), pinToolDTO->getWidth(), pinToolDTO->getHeight());
        world.addPinTool(pinTool);
    }
}

void SDL_Runner::run() {
    musicPlayer.playBackgroundMusic();

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
                    this->addChell(newChell);
                    break;
                }
                case PROTOCOL_PLAYER_CHELL_ID: {
                    auto chellId = (PlayerChellIdDTO *) newItem;
                    this->addPlayerId(chellId);
                    break;
                }
                case PROTOCOL_BUTTON_DATA: {
                    auto buttonData = (ButtonDTO *) newItem;
                    this->addButton(buttonData);
                    break;
                }
                case PROTOCOL_GATE_DATA: {
                    auto gateDTO = (GateDTO*) newItem;
                    this->addGate(gateDTO);
                    break;
                }
                case PROTOCOL_ACID_DATA: {
                    auto acidDTO = (AcidDTO*) newItem;
                    this->addAcid(acidDTO);
                    break;
                }
                case PROTOCOL_ROCK_BLOCK_DATA: {
                    auto rockBlockDTO = (RockBlockDTO*) newItem;
                    this->addRockBlock(rockBlockDTO);
                    break;
                }
                case PROTOCOL_METAL_BLOCK_DATA: {
                    auto metalBlockDTO = (MetalBlockDTO*) newItem;
                    this->addMetalBlock(metalBlockDTO);
                    break;
                }
                case PROTOCOL_METAL_DIAGONAL_BLOCK_DATA: {
                    auto diagonalMetalBlockDTO = (MetalDiagonalBlockDTO*) newItem;
                    this->addMetalDiagonalBlock(diagonalMetalBlockDTO);
                    break;
                }
                case PROTOCOL_ENERGY_TRANSMITTER_DATA: {
                    auto energyTransmitterDTO = (EnergyTransmitterDTO*) newItem;
                    this->addEnergyTransmitter(energyTransmitterDTO);
                    break;
                }
                case PROTOCOL_ENERGY_RECEIVER_DATA: {
                    auto energyReceiverDTO = (EnergyReceiverDTO*) newItem;
                    this->addEnergyReceiver(energyReceiverDTO);
                    break;
                }
                case PROTOCOL_ENERGY_BARRIER_DATA: {
                    auto energyBarrierDTO = (EnergyBarrierDTO*) newItem;
                    this->addEnergyBarrier(energyBarrierDTO);
                    break;
                }
                case PROTOCOL_ROCK_DATA: {
                    auto rockDTO = (RockDTO*) newItem;
                    this->addRock(rockDTO);
                    break;
                }
                case PROTOCOL_CAKE_DATA: {
                    auto cakeDTO = (CakeDTO*) newItem;
                    this->addCake(cakeDTO);
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
                        this->addChell(newChell);
                        break;
                    }
                    case PROTOCOL_BUTTON_CHANGE_STATE: {
                        auto buttonStateDTO = (ButtonStateDTO*) newItem;
                        this->setButtonState(buttonStateDTO);
                        break;
                    }
                    case PROTOCOL_GATE_CHANGE_STATE: {
                        auto gateStateDTO = (GateStateDTO*) newItem;
                        this->setGateState(gateStateDTO);
                        break;
                    }
                    case PROTOCOL_ROCK_DATA: {
                        auto rockDTO = (RockDTO*)newItem;
                        this->addRock(rockDTO);
                        break;
                    }
                    case PROTOCOL_ENERGY_BALL_DATA: {
                        auto energyBallDTO = (EnergyBallDTO*) newItem;
                        this->addEnergyBall(energyBallDTO);
                        break;
                    }
                    case PROTOCOL_PORTAL_DATA: {
                        auto portalDTO = (PortalDTO*) newItem;
                        this->addPortal(portalDTO);
                        break;
                    }
                    case PROTOCOL_PIN_TOOL_DATA: {
                        auto pinToolDTO = (PinToolDTO*) newItem;
                        this->addPinTool(pinToolDTO);
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
        SDL_Delay(DELAY);
    }
}

void SDL_Runner::getRealPos(int &x, int &y, int x_m, int y_m) {
    world.obtainXY(x, y, x_m, y_m, renderer);
}
