//
// Created by jonathanmedina on 20/06/19.
//

#include <Server/Model/constants.h>
#include "PortalBlueView.h"


PortalBlueView::PortalBlueView(SDL_Texture *texture, Renderer &renderer, int16_t tilted, int x, int y) :
View(x, y),
portal(texture, renderer, 210, 210, 77, 21, 4, 4, 1, 0, AnimationState::onRepeat), tilted(tilted) {
}

void PortalBlueView::draw(Camera &camera) {
    if (tilted == STRAIGHT) {
        portal.drawMovingSprite(camera, this->getDst(), 0);
    } else if (tilted == LEFT) {
        portal.drawMovingSprite(camera, this->getDst(), 45);
    } else if (tilted == RIGHT) {
        portal.drawMovingSprite(camera, this->getDst(), -45);
    }
}
