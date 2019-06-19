//
// Created by jonathanmedina on 08/06/19.
//

#include "GateView.h"


GateView::GateView(int id, SDL_Texture *texture, Renderer &renderer, int x, int y) :
        View(x, y), id(id),
        closedGate(texture, renderer),
        gate(texture, renderer, 193, 385, 1, 2051, 10, 19, 1, 1, AnimationState::oneTime) {
        closedGate.setSourceRect(1, 21, 192, 385);
        this->state = GateState::closed;
}

void GateView::draw(Camera &camera) {
    if (this->state == GateState::closed) {
        closedGate.draw(camera, this->getDst());
    } else if (this->state == GateState::open) {
        gate.drawMovingSprite(camera, this->getDst());
    } else if (this->state == GateState::isClosingBack) {
        gate.drawMovingSprite(camera, this->getDst());
        if (gate.done()) {
            this->state = GateState::closed;
            gate.setState(AnimationState::oneTime);
            this->gate.setTimePerSprite(4);
        }
    }
}

int GateView::getId() const {
    return id;
}

void GateView::close() {
    gate.setState(AnimationState::revert);
    this->state = GateState::isClosingBack;
    this->gate.setTimePerSprite(1);
}

void GateView::open() {
    this->state = GateState::open;
}
