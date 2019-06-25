//
// Created by jonathanmedina on 28/05/19.
//

#include "ChellAnimationView.h"

ChellAnimationView::ChellAnimationView(int id, SDL_Texture *dyingTexture, SDL_Texture *firingTexture,
                                       SDL_Texture *flyingTexture, SDL_Texture* restingTexture,
                                       SDL_Texture *runningTexture, SDL_Texture *winningTexture, Renderer &renderer,
                                       int x, int y) :
                                       View(x, y), id(id), runningRightChell(runningTexture, renderer, 201, 220, 0, 0, 12, 12, 1, 0, AnimationState::onRepeat),
                                       standStillChell(restingTexture, renderer, 122, 222, 0, 0, 7, 7, 1, 0, AnimationState::onRepeat),
                                       firingChell(firingTexture, renderer, 190, 212, 0, 0, 5, 5, 1, 0, AnimationState::oneTime),
                                       flyingChell(flyingTexture, renderer, 144, 221, 1, 0, 4, 4, 1, 0, AnimationState::onRepeat),
                                       dyingChell(dyingTexture, renderer, 199, 274, 0, 0, 12 , 72, 1, 1, AnimationState::oneTime),
                                       winningChell(winningTexture, renderer, 163, 243, 0, 0, 14, 79, 1, 1, AnimationState::onRepeat),state(standing), tiltedState(NO)
                                       {
    dyingChell.setTimePerSprite(6);
}


void ChellAnimationView::draw(Camera& camera) {
    double angle = getAngle();

    if (state == standing) {
        standStillChell.drawMovingSprite(camera, this->getDst(), angle);
    } else if (state == runningLeft) {
        runningRightChell.drawMovingSprite(camera, this->getDst(), angle, SDL_FLIP_HORIZONTAL);
    } else if (state == runningRight) {
        runningRightChell.drawMovingSprite(camera, this->getDst(), angle);
    } else if (state == firing) {
        firingChell.drawMovingSprite(camera, this->getDst(), angle);
    } else if (state == flying) {
        flyingChell.drawMovingSprite(camera, this->getDst());
    } else if (state == dying) {
        dyingChell.drawMovingSprite(camera, this->getDst(), angle);
    } else if (state == winning) {
        winningChell.drawMovingSprite(camera, this->getDst());
    }
}

double ChellAnimationView::getAngle() const {
    double angle;
    if (tiltedState == TILTEDRIGHT) {
        angle = 45;
    } else if (tiltedState == TILTEDLEFT) {
        angle = 315;
    } else if (tiltedState == NO){
        angle = 0;
    }
    return angle;
}

void ChellAnimationView::setState(ChellState state) {
    if (this->state == ChellState::firing) {
        if (this->firingChell.done()) {
            this->firingChell.reset();
        } else {
            return;
        }
    }
    this->state = state;
}

int ChellAnimationView::getId() const {
    return id;
}

bool ChellAnimationView::isDead() {
    return dyingChell.done();
}

void ChellAnimationView::setTiltedState(ChellIsTilted state) {
    this->tiltedState = state;
}

ChellState ChellAnimationView::getState() const {
    return state;
}
