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
    ChellAnimationView* chell = new ChellAnimationView(textureFactory.getTextureByName(chell_file_name),renderer);
    chell->setDestRect(200,200,201,220);
    Camera camera(1000, 1000, chell->getPosition());
    WorldView world(camera);
    ChellAnimationView* chell2 = new ChellAnimationView(textureFactory.getTextureByName(chell_file_name),renderer);
    chell2->setDestRect(-200,-100,201,220);
    ChellAnimationView* chell3 = new ChellAnimationView(textureFactory.getTextureByName(chell_file_name),renderer);
    chell3->setDestRect(100,-100,201,220);

    world.addChell(chell);
    world.addChell(chell2);
    world.addChell(chell3);


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
        world.draw();
        renderer.render();
    }
}
