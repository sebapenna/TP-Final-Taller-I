//
// Created by jonathanmedina on 26/05/19.
//

#include <iostream>
#include "AnimatedSprite.h"



AnimatedSprite::AnimatedSprite(const std::string &filename, Renderer &renderer,
                               int width, int height,
                               int startX, int startY,
                               int totalColumns, int amountSprites, int finalX, int finalY,
                               int finalWidth, int finalHeight, int offSetX, int offSetY) :
        Sprite(filename, renderer),
        width(width), height(height),
        startX(startX), startY(startY),
        totalColumns(totalColumns), amountSprites(amountSprites), offSetX(offSetX), offSetY(offSetY),
        currentSprite(1), i(0), j(0), currentTime(1), timePerSprite(DEFAULT_TIME_PER_SPRITE) {
    this->setSourceRect(startX, startY, width, height);
    this->setDestRect(finalX, finalY, finalWidth, finalHeight);
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

void AnimatedSprite::drawMovingSprite() {
    this->moveNextSprite();
    this->draw();
}

void AnimatedSprite::setTimePerSprite(Uint32 t) {
    timePerSprite = t;
}

void AnimatedSprite::reset() {
    currentSprite = 0;
    i = 0;
    j = 0;
}
