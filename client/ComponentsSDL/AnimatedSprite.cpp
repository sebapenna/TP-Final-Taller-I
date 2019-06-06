//
// Created by jonathanmedina on 26/05/19.
//

#include <iostream>
#include "AnimatedSprite.h"


// PUEDO HACER UN SPRITE FACTORY
AnimatedSprite::AnimatedSprite(SDL_Texture* texture, Renderer &renderer,
                               int width, int height,
                               int startX, int startY,
                               int totalColumns, int amountSprites, int offSetX, int offSetY) :
        Sprite(texture, renderer),
        width(width), height(height),
        startX(startX), startY(startY),
        totalColumns(totalColumns), amountSprites(amountSprites), offSetX(offSetX), offSetY(offSetY),
        currentSprite(1), i(0), j(0), currentTime(1), timePerSprite(DEFAULT_TIME_PER_SPRITE) {
    this->setSourceRect(startX, startY, width, height);
}


void AnimatedSprite::moveNextSprite() {
    if (currentTime % timePerSprite != 0) { // Cantidad de frames por sprite.
        currentTime++;
        return;
    }
    currentTime++;
    if(amountSprites == currentSprite) { // Reset
        i = 0;
        j = 0;
        currentSprite = 1;
    } else {
        if (totalColumns-1 == i) {
            i = 0;
            j++;
        } else {
            i++;
        }
        currentSprite++;
    }
    this->setSourceXY(i * width + startX + offSetX * i, j * height + startY + offSetY * j);
}

void AnimatedSprite::drawMovingSprite(Camera& camera, SDL_Rect* dstRect) {
    this->moveNextSprite();
    this->draw(camera, dstRect);
}

void AnimatedSprite::drawMovingSprite(Camera& camera, SDL_Rect* dstRect, SDL_RendererFlip flip) {
    this->moveNextSprite();
    this->draw(camera, dstRect, flip);
}

void AnimatedSprite::setTimePerSprite(Uint32 t) {
    timePerSprite = t;
}

void AnimatedSprite::reset() {
    currentSprite = 0;
    i = 0;
    j = 0;
}
