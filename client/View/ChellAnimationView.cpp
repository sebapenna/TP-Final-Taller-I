//
// Created by jonathanmedina on 28/05/19.
//

#include "ChellAnimationView.h"

ChellAnimationView::ChellAnimationView(int id, SDL_Texture* texture, Renderer& renderer, int x, int y) : id(id),
View(x, y),
runningRightChell(texture, renderer, 201, 220, 1, 3983, 12, 12, 1, 0, AnimationState::onRepeat),
standStillChell(texture, renderer, 122, 222, 1, 2080, 7, 7, 1, 0, AnimationState::onRepeat),
firingChell(texture, renderer, 190, 212, 1, 2546, 5, 5, 1, 0, AnimationState::oneTime),
flyingChell(texture, renderer, 144, 221, 1, 1117, 4, 4, 1, 0, AnimationState::onRepeat),
dyingChell(texture, renderer, 199, 274, 1, 8340, 12 , 72, 1, 1, AnimationState::oneTime),state(standing), tiltedState(NO) {
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
