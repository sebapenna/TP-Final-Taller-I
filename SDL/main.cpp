#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <exception>
#include "Window.h"
#include "Renderer.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "ChellAnimationView.h"
#include "TextureFactory.h"
#include "WorldView.h"

int main(int argc, char** argv){
    // Iniciar socketprotocol
    try {
        std::string title("hello world");
        Window window(title, 1000, 1000, SDL_WINDOW_SHOWN);
        Renderer renderer(window);

        //Sprite sprite(file,renderer);
        //sprite.setSourceRect(0,0,200,200);
        //sprite.setDestRect(0,0,200,200);
        //sprite.draw();

        // Chell resting idle
        // AnimatedSprite sprite("chell.png", renderer, 122, 222, 1, 2080, 7, 7, 0, 0, 122, 222, 1, 0);

        // Chell running
        // AnimatedSprite sprite("chell.png", renderer, 201, 220, 1, 3983, 12, 12, 0, 0, 201, 220, 1, 0);

        // Chell turning around
        //AnimatedSprite sprite("chell.png", renderer, 292, 209, 1, 3753, 8, 8, 0, 0, 292, 209, 1, 0);

        // Chell firing
        //AnimatedSprite sprite("chell.png", renderer, 190, 212, 1, 2546, 5, 5, 0, 0, 190, 212, 1, 0);

        // Chell dying
        //AnimatedSprite sprite("chell.png", renderer, 199, 274, 1, 8340, 12 , 72, 0, 0, 199, 273, 1, 1);

        /*while (i<5000) {
            renderer.clearRender();
            sprite.drawMovingSprite();
            i++;
            renderer.render();
        }*/
        SDL_Event e;
        TextureFactory factory;
        factory.init(renderer);
        std::string chell_file_name("chell");
        ChellAnimationView* chell = new ChellAnimationView(factory.getTextureByName(chell_file_name),renderer);
        chell->setDestRect(200,200,201,220);
        Camera camera(1000, 1000, chell->getDst());
        WorldView world(camera);
        ChellAnimationView* chell2 = new ChellAnimationView(factory.getTextureByName(chell_file_name),renderer);
        chell2->setDestRect(-200,-100,201,220);
        ChellAnimationView* chell3 = new ChellAnimationView(factory.getTextureByName(chell_file_name),renderer);
        chell3->setDestRect(100,-100,201,220);

        world.addChell(chell);
        world.addChell(chell2);
        world.addChell(chell3);

        while (true) {
            renderer.clearRender();
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
                            chell->moveToTheRight(10);
                            break;
                        case SDLK_a:
                            chell->moveToTheLeft(10);
                            break;
                        case SDLK_UP:
                            world.moveCameraUp();
                            break;
                        case SDLK_LEFT:
                            world.moveCameraLeft();
                            break;
                        case SDLK_RIGHT:
                            world.moveCameraRight();
                            break;
                        case SDLK_DOWN:
                            world.moveCameraDown();
                            break;
                        default:
                            break;
                    }
                }
            }
            world.draw();
            renderer.render();
        }

        //renderer.fill(0x00, 0xFF, 0xFF, 0xFF);
        //renderer.render();
        SDL_Delay(5000);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
