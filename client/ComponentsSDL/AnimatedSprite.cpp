//
// Created by jonathanmedina on 26/05/19.
//

#include <iostream>
#include "AnimatedSprite.h"


// PUEDO HACER UN SPRITE FACTORY
AnimatedSprite::AnimatedSprite(SDL_Texture* texture, Renderer &renderer,
                               int width, int height,
                               int startX, int startY,
                               int totalColumns, int amountSprites,
                               int offSetX, int offSetY, AnimationState animationState) :
        Sprite(texture, renderer),
        width(width), height(height),
        startX(startX), startY(startY),
        totalColumns(totalColumns), amountSprites(amountSprites), offSetX(offSetX), offSetY(offSetY),
        currentSprite(1), i(0), j(0),
        animationState(animationState),
        currentTime(1), timePerSprite(DEFAULT_TIME_PER_SPRITE) {
    this->setSourceRect(startX, startY, width, height);
}


void AnimatedSprite::moveNextSprite() {
    if (currentTime % timePerSprite != 0) { // Cantidad de frames por sprite.
        currentTime++;
        return;
    }
    currentTime++;
    if (animationState == AnimationState::revert) {
        if (!historyAnimation.size()) return;
        if (i == 0) {
            i = totalColumns-1;
            j--;
        } else {
            i--;
        }

        SDL_Rect lastSrc = historyAnimation.back();
        historyAnimation.pop_back();
        currentSprite--;
        this->setSourceRect(lastSrc.x, lastSrc.y, lastSrc.w, lastSrc.h);
        return;
    }
    if((amountSprites == currentSprite) && (animationState == AnimationState::onRepeat)) { // Reset
        this->reset();
    } else if (((amountSprites != currentSprite) && (animationState == AnimationState::oneTime)
    || (animationState == AnimationState::onRepeat))) {
        if (totalColumns-1 == i) {
            i = 0;
            j++;
        } else {
            i++;
        }
        currentSprite++;
    }
    this->setSourceXY(i * width + startX + offSetX * i, j * height + startY + offSetY * j);
    historyAnimation.push_back(this->getSrc());


}

void AnimatedSprite::drawMovingSprite(Camera& camera, SDL_Rect* dstRect) {
    this->moveNextSprite();
    this->draw(camera, dstRect);
}

void AnimatedSprite::drawMovingSprite(Camera& camera, SDL_Rect* dstRect, double angle, SDL_RendererFlip flip) {
    this->moveNextSprite();
    this->draw(camera, dstRect, angle, flip);

}

void AnimatedSprite::setTimePerSprite(Uint32 t) {
    timePerSprite = t;
}

bool AnimatedSprite::done() {
    return (((amountSprites == currentSprite) && (animationState != AnimationState::revert)) ||
            ((currentSprite == 1) && (animationState == AnimationState::revert)));
}

void AnimatedSprite::reset() {
    historyAnimation.clear();
    currentSprite = 1;
    i = 0;
    j = 0;
}

void AnimatedSprite::setState(AnimationState state) {
    this->animationState = state;
}
