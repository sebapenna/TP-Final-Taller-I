#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <exception>
#include "ComponentsSDL/Window.h"
#include "ComponentsSDL/Renderer.h"
#include "View/ChellAnimationView.h"
#include "TextureFactory.h"
#include "WorldView.h"
#include "View/BlockViewMetal.h"
#include "View/BlockViewRock.h"
#include <queue>
#include "SDL_Runner.h"
#include "FakeServer.h"
#include <Common/SafeQueue.h>
#include <Common/ProtectedBlockingQueue.h>
#include <Common/ProtocolTranslator/ProtocolTranslator.h>
#include <Common/ProtocolTranslator/MoveLeftDTO.h>
#include <Common/ProtocolTranslator/MoveRightDTO.h>

int main(int argc, char** argv){
    /* Iniciar socketprotocol
    Socket socket;
    socket.connect("localhost", "8080");
    char listMsg[] = {8};
    socket.sendMessage(listMsg, 1);
    int listLen = 0;
    socket.recvMessage((char*)&listLen, 4);
    std::vector<char> list(listLen);
    socket.recvMessage(list.data(), listLen);
    std::string listString = list.data();
    std::cout << listString << std::endl;*/
    
    try {
        std::string title("hello world");
        // Window window(title, 1000, 1000, SDL_WINDOW_SHOWN);
        // Renderer renderer(window);

        // Chell turning around
        //AnimatedSprite sprite("chell.png", renderer, 292, 209, 1, 3753, 8, 8, 0, 0, 292, 209, 1, 0);

        // Chell firing
        //AnimatedSprite sprite("chell.png", renderer, 190, 212, 1, 2546, 5, 5, 0, 0, 190, 212, 1, 0);

        // Chell dying
        //AnimatedSprite sprite("chell.png", renderer, 199, 274, 1, 8340, 12 , 72, 0, 0, 199, 273, 1, 1);

        // TextureFactory factory;
        // factory.init(renderer);
        /*std::string chell_file_name("chell");
        ChellAnimationView* chell = new ChellAnimationView(factory.getTextureByName(chell_file_name),renderer);
        chell->setDestRect(200,200,201,220);
        Camera camera(1000, 1000, chell->getPosition());
        WorldView world(camera);
        ChellAnimationView* chell2 = new ChellAnimationView(factory.getTextureByName(chell_file_name),renderer);
        chell2->setDestRect(-200,-100,201,220);
        ChellAnimationView* chell3 = new ChellAnimationView(factory.getTextureByName(chell_file_name),renderer);
        chell3->setDestRect(100,-100,201,220);

        world.addChell(chell);
        world.addChell(chell2);
        world.addChell(chell3);*/

        /*
        std::string block_file_name("block");
        for (int startX = -2000; startX<7000; startX+=128) {
            for (int startY = -2000; startY<7000; startY+=128) {
                View* block = new BlockViewRock(factory.getTextureByName(block_file_name),renderer);
                block->setDestRect(startX, startY, 128, 128);
                world.addView(block);
            }
            View* block = new BlockViewMetal(factory.getTextureByName(block_file_name),renderer);
            block->setDestRect(startX, 400, 128,128);
            world.addView(block);
        }*/
        SafeQueue safeQueue;
        ProtectedBlockingQueue blockingQueue;
        SDL_Runner sdlRunner(title, safeQueue);
        sdlRunner.start();
        FakeServer server(blockingQueue, safeQueue);
        server.start();
        /*
        SDL_Runner sdlRunner(safeQueue);
        sdlRunner.start();
        ServerFicticio server(queueBlockingQueue, safeQueue);
        server.start();
        FactoryGeneratorEventsUser eventCatcher();
        */
        SDL_Event e;
        while (true) {
            //renderer.clearRender();
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    return 0;
                } else if (e.type == SDL_MOUSEBUTTONDOWN){
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        //chell.fire();
                    }
                } else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_d:
                            blockingQueue.push((void*) new MoveLeftDTO());
                            break;
                        case SDLK_a:
                            blockingQueue.push((void*) new MoveRightDTO());
                            break;
                        case SDLK_w:
                            //eventCatcher.jump();
                        default:
                            break;
                    }
                }
            }
            //world.draw();
            //renderer.render();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
