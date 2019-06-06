//
// Created by jonathanmedina on 05/06/19.
//

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
    ChellAnimationView* chell = new ChellAnimationView(1, textureFactory.getTextureByName(chell_file_name),renderer);
    Position chellPos(200,200);
    //chell->setDestRect(200,200,201,220);
    Camera camera(1000, 1000, chell->getPosition());
    WorldView world(camera);

    //ChellAnimationView* chell2 = new ChellAnimationView(2, textureFactory.getTextureByName(chell_file_name),renderer);
    //Position chell2Pos(-200,-100);
    //chell2->setDestRect(-200,-100,201,220);
    //ChellAnimationView* chell3 = new ChellAnimationView(3, textureFactory.getTextureByName(chell_file_name),renderer);
    //Position chell3Pos(100,-100);
    //chell3->setDestRect(100,-100,201,220);

    world.addChell(chell, chellPos);
    //world.addChell(chell2, chell2Pos);
    //world.addChell(chell3, chell3Pos);

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
        FakeChellNewPosition* newChell = (FakeChellNewPosition*) safeQueue.getTopAndPop();
        if (newChell) {
            ChellAnimationView* chell2 = new ChellAnimationView(newChell->getClassId(), textureFactory.getTextureByName(chell_file_name),renderer);
            Position chell2Pos(newChell->getX(),newChell->getY());
            chell2->setDestRect(newChell->getX(),newChell->getY(),201,220);
            world.addChell(chell2, chell2Pos);
        }
        world.draw();
        renderer.render();
    }
}