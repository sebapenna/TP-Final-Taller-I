//
// Created by jonathanmedina on 26/05/19.
//

#include "Sprite.h"
#include "SDLException.h"
#include <SDL2/SDL_image.h>

Sprite::Sprite(SDL_Texture* texture, Renderer& renderer) :
    renderer(renderer), texture(texture) {
}

void Sprite::draw(Camera &camera, SDL_Rect* dstRect) {
    camera.draw(texture, &srcRect, dstRect, this->renderer);
}

void Sprite::draw(Camera &camera, SDL_Rect* dstRect, SDL_RendererFlip flip) {
    camera.draw(texture, &srcRect, dstRect, this->renderer, flip);

}

void Sprite::setSourceXY(int x, int y) {
    srcRect.x = x;
    srcRect.y = y;
}


void Sprite::setSourceRect(int x, int y, int w, int h) {
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;
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

SDL_Rect Sprite::getSrc() {
    return srcRect;
}

SDL_Texture *Sprite::getTexture() {
    return texture;
}
