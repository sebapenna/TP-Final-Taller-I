#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "Window.h"

class Renderer {
private:
    Window& window;
    SDL_Renderer* renderer;
    int windowWidth;
    int windowHeight;

public:
    Renderer(Window& window);
    ~Renderer();

    void copyTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst, double angle, SDL_Point* center, SDL_RendererFlip flip);
    void copyTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst);
    void copyTexture(SDL_Texture* texture, SDL_Rect* dst=NULL);
    void clearRender();
    void render();
    void fill(int r, int g, int b, int alpha);
    SDL_Renderer* getRenderer();
    int getWindowWidth();
    int getWindowHeight();
    Uint32 getWindowID();
};


#endif
