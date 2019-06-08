//
// Created by jonathanmedina on 05/06/19.
//

#include <Common/ProtocolTranslator/ChellDTO.h>
#include <iostream>
#include <Common/ProtocolTranslator/PlayerChellIdDTO.h>
#include "SDL_Runner.h"
#include "ComponentsSDL/Window.h"
#include "ComponentsSDL/Renderer.h"
#include "View/ChellAnimationView.h"
#include "WorldView.h"
#include "View/BlockViewRock.h"
#include "View/BlockViewMetal.h"

SDL_Runner::SDL_Runner(std::string& title, SafeQueue &safeQueue) : safeQueue(safeQueue), connected(true), window(title, 1000, 1000, SDL_WINDOW_SHOWN), renderer(window), textureFactory() {
    textureFactory.init(renderer);
}

void SDL_Runner::run() {
    std::string chell_file_name("chell");
    WorldView world;

    std::string block_file_name("block");
    for (int startX = -2000; startX<7000; startX+=128) {
        for (int startY = -2000; startY<7000; startY+=128) {
            View* block = new BlockViewRock(textureFactory.getTextureByName(block_file_name),renderer);
            block->setDestRect(startX, startY, 128, 128);
            world.addView(block);
        }
        View* block = new BlockViewMetal(textureFactory.getTextureByName(block_file_name),renderer);
        block->setDestRect(startX, 400, 128,128);
        world.addView(block);
    }

    while (connected) {
        renderer.clearRender();
        auto newItem = (ProtocolDTO*) safeQueue.getTopAndPop();
        if (newItem) {
            if (newItem->getClassId() == PROTOCOL_CHELL_DATA) {
                auto newChell = (ChellDTO *) newItem;
                auto chell2 = new ChellAnimationView(newChell->getId(),
                                                     textureFactory.getTextureByName(chell_file_name), renderer);
                Position chell2Pos(newChell->getX(), newChell->getY());
                chell2->setDestRect(newChell->getX(), newChell->getY(), newChell->getWidth(), newChell->getHeight());
                world.addChell(chell2, chell2Pos);
                if (newChell->getMoving()) {
                    if (newChell->getDirection() == WEST) {
                        world.setChellState(newChell->getId(), State::runningLeft);
                    } else {
                        world.setChellState(newChell->getId(), State::runningRight);
                    }
                } else {
                    world.setChellState(newChell->getId(), State::standing);
                }
                if (newChell->getJumping()) {
                    world.setChellState(newChell->getId(), State::flying);
                }
            } else if (newItem->getClassId() == PROTOCOL_PLAYER_CHELL_ID) {
                auto chellId = (PlayerChellIdDTO*) newItem;
                world.setCamara(chellId->getChellId(), 1000, 1000);
                this->myChellId = chellId->getChellId();
            }
        }
        world.draw();
        renderer.render();
    }
}
