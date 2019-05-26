#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <exception>
#include "Window.h"
#include "Renderer.h"
#include "Sprite.h"

int main(int argc, char** argv){
    try {
        std::string title("hello world");
        Window window(title, 1000, 1000, SDL_WINDOW_SHOWN);
        Renderer renderer(window);
        std::string file("block.png");
        Sprite sprite(file,renderer);
        sprite.setSourceRect(0,0,200,200);
        sprite.setDestRect(0,0,200,200);
        sprite.draw();
        renderer.render();
        //renderer.fill(0x00, 0xFF, 0xFF, 0xFF);
        //renderer.render();
        SDL_Delay(5000);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
