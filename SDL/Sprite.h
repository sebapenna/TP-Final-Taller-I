//
// Created by jonathanmedina on 26/05/19.
//

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Renderer.h"
#include "Camera.h"
class Camera;

class Sprite {
private:
    SDL_Texture* texture;
    Renderer& renderer;
    SDL_Rect srcRect;

public:
    Sprite(SDL_Texture* texture, Renderer &renderer);
    void draw(Camera& camera, SDL_Rect* dstRect);
    void draw(Camera &camera, SDL_Rect* dstRect, SDL_RendererFlip flip);
    void setSourceW(int w);
    void setTexture(SDL_Texture *newTexture);
    void setAlphaMod(Uint8 alpha);
    SDL_Rect* getSrc();
    SDL_Texture* getTexture();
    void setSourceRect(int x, int y, int w, int h);

protected:
    void setSourceXY(int x, int y);
};


#endif //SPRITE_H
