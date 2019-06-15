//
// Created by jonathanmedina on 13/06/19.
//

#include "EnergyReceiverView.h"

EnergyReceiverView::EnergyReceiverView(int id, SDL_Texture *texture, Renderer &renderer, int x, int y) :
        View(x, y), id(id),
        energyReceiverSprite(texture, renderer),
        energyReceiverAnimation(texture, renderer, 200, 197, 1, 2102, 6, 6, 1, 0, AnimationState::oneTime),
        state(EnergyReceiverState::disable) {
    energyReceiverSprite.setSourceRect(1, 2102, 200, 197);

}

void EnergyReceiverView::draw(Camera &camera) {
    if (state == EnergyReceiverState::disable) {
        energyReceiverSprite.draw(camera, this->getDst());
    } else if (state == EnergyReceiverState::enable) {
        energyReceiverAnimation.drawMovingSprite(camera, this->getDst());
    }
}

void EnergyReceiverView::activate() {
    this->state = EnergyReceiverState::enable;
}

int EnergyReceiverView::getId() const {
    return id;
}
