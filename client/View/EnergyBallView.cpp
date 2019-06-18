//
// Created by jonathanmedina on 18/06/19.
//

#include "EnergyBallView.h"

EnergyBallView::EnergyBallView(int id, SDL_Texture *texture, Renderer &renderer, int x, int y) :
        View(x, y), id(id),
        ball(texture, renderer, 61, 61, 1, 4431, 3, 3, 1, 0, AnimationState::onRepeat) {
}

void EnergyBallView::draw(Camera &camera) {
    ball.drawMovingSprite(camera, this->getDst());
}

int EnergyBallView::getId() const {
    return id;
}

