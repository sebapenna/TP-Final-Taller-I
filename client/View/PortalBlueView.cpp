//
// Created by jonathanmedina on 20/06/19.
//

#include <Server/Model/constants.h>
#include "PortalBlueView.h"


PortalBlueView::PortalBlueView(int id, SDL_Texture *texture, Renderer &renderer, int16_t tilted, int x, int y) :
View(x, y), id(id),
portal(texture, renderer, 209, 210, 78, 21, 4, 4, 1, 0, AnimationState::onRepeat), tilted(tilted) {
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

int PortalBlueView::getId() const {
    return id;
}
