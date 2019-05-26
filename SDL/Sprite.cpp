//
// Created by jonathanmedina on 26/05/19.
//

#include "Sprite.h"
#include "SDLException.h"
#include <SDL2/SDL_image.h>

Sprite::Sprite(const std::string &filename, Renderer& renderer) :
    renderer(renderer) {
    this->texture = loadTexture(filename);
}

Sprite::~Sprite() {}

void Sprite::draw() {
    renderer.copyTexture(texture, &srcRect, &dstRect);
}

void Sprite::setSourceXY(int x, int y) {
    srcRect.x = x;
    srcRect.y = y;
}

void Sprite::setDestXY(int x, int y) {
    dstRect.x = x;
    dstRect.y = y;
}

void Sprite::setSourceRect(int x, int y, int w, int h) {
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;
}

void Sprite::setDestRect(int x, int y, int w, int h) {
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;
}

void Sprite::setTexture(SDL_Texture *newTexture) {
    this->texture = newTexture;
}


void Sprite::setAlphaMod(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture, alpha);
}



void Sprite::setSourceW(int w) {
    srcRect.w = w;
}

void Sprite::setDestW(int w) {
    dstRect.w = w;
}

int Sprite::getDestX() {
    return dstRect.x;
}

int Sprite::getDestY() {
    return dstRect.y;
}

SDL_Texture *Sprite::loadTexture(const std::string& filename) {
    IMG_Init(IMG_INIT_PNG);
    SDL_Texture* texture = IMG_LoadTexture(this->renderer.getRenderer(), filename.c_str());
    if (!texture) {
        throw SDLException("Error while loading texture", SDL_GetError());
    }
    return texture;
}
