//
// Created by jonathanmedina on 08/06/19.
//

#include "AcidView.h"


AcidView::AcidView(SDL_Texture *texture, Renderer &renderer, int x, int y) :
        View(x, y),
        acid(texture, renderer, 300, 61, 1, 1545, 8, 8, 1, 0, AnimationState::onRepeat) {
}

void AcidView::draw(Camera &camera) {
    acid.drawMovingSprite(camera, this->getDst());
}

