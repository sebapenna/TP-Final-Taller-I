//
// Created by jonathanmedina on 13/06/19.
//

#include <Server/Model/constants.h>
#include "EnergyTransmitterView.h"

EnergyTransmitterView::EnergyTransmitterView(int id, SDL_Texture *texture, Renderer &renderer, int16_t orientation, int x, int y) :
    View(x, y), id(id),
    notTransmiting(texture, renderer),
    transmiteAnimation(texture, renderer, 192, 192, 385, 878, 4, 4, 1, 0, AnimationState::oneTime),
    orientation(orientation), state(EnergyTransmitterState::notTransmiting) {
    notTransmiting.setSourceRect(385, 878, 192, 192);
    transmiteAnimation.setTimePerSprite(2);
    this->setAngle();
}

int EnergyTransmitterView::getId() const {
    return id;
}

void EnergyTransmitterView::draw(Camera &camera) {
    if (state == EnergyTransmitterState::notTransmiting) {
        notTransmiting.draw(camera, this->getDst(), angle);
    } else if (state == EnergyTransmitterState::transmiting) {
        transmiteAnimation.drawMovingSprite(camera, this->getDst(), angle);
        if (transmiteAnimation.done()) {
            transmiteAnimation.reset();
            this->state = EnergyTransmitterState::notTransmiting;
        }
    }
}

void EnergyTransmitterView::transmite() {
    this->state = EnergyTransmitterState::transmiting;
}

void EnergyTransmitterView::setAngle() {
    if (this->orientation == O_N) {
        this->angle = 90;
    } else if (this->orientation == O_S) {
        this->angle = 270;
    } else if (this->orientation == O_E) {
        this->angle = 180;
    } else if (this->orientation == O_O) {
        this->angle = 0;
    }
}
