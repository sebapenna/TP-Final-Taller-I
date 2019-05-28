#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <exception>
#include "Window.h"
#include "Renderer.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

int main(int argc, char** argv){
    try {
        std::string title("hello world");
        Window window(title, 1000, 1000, SDL_WINDOW_SHOWN);
        Renderer renderer(window);
        std::string file("block.png");
        //Sprite sprite(file,renderer);
        //sprite.setSourceRect(0,0,200,200);
        //sprite.setDestRect(0,0,200,200);
        //sprite.draw();
        int i = 0;

        // Chell resting idle
        // AnimatedSprite sprite("chell.png", renderer, 122, 222, 1, 2080, 7, 7, 0, 0, 122, 222, 1, 0);

        // Chell running
        AnimatedSprite sprite("chell.png", renderer, 201, 220, 1, 3983, 12, 12, 0, 0, 201, 220, 1, 0);

        // Chell turning around
        //AnimatedSprite sprite("chell.png", renderer, 292, 209, 1, 3753, 8, 8, 0, 0, 292, 209, 1, 0);

        // Chell firing
        // AnimatedSprite sprite("chell.png", renderer, 190, 212, 1, 2546, 5, 5, 0, 0, 190, 212, 1, 0);

        // Chell dying
        //AnimatedSprite sprite("chell.png", renderer, 199, 274, 1, 8340, 12 , 72, 0, 0, 199, 273, 1, 1);
        while (i<5000) {
            renderer.clearRender();
            sprite.drawMovingSprite(0,SDL_FLIP_HORIZONTAL);
            i++;
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
