//
// Created by jonathanmedina on 26/05/19.
//

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Renderer.h"

class Sprite {
private:
    SDL_Texture* texture;
    Renderer& renderer;
    SDL_Rect srcRect;
    SDL_Rect dstRect;

public:
    Sprite(const std::string &filename, Renderer &renderer);
    ~Sprite();
    void draw();
    void draw(double angle, SDL_RendererFlip flip);
    void setSourceXY(int x, int y);
    void setDestXY(int x, int y);
    void setSourceRect(int x, int y, int w, int h);
    void setDestRect(int x, int y, int w, int h);
    void setSourceW(int w);
    void setDestW(int w);
    void setTexture(SDL_Texture *newTexture);
    void setAlphaMod(Uint8 alpha);
    int getDestX();
    int getDestY();
private:
    SDL_Texture *loadTexture(const std::string &basicString);
};


#endif //SPRITE_H
