//
// Created by jonathanmedina on 20/06/19.
//

#include <Server/Model/constants.h>
#include "PortalOrangeView.h"

PortalOrangeView::PortalOrangeView(int id, SDL_Texture *texture, Renderer &renderer, int16_t tilted, int x, int y) :
View(x, y), id(id),
portal(texture, renderer, 209, 210, 77, 234, 4, 4, 1, 0, AnimationState::onRepeat), tilted(tilted) {
}

void PortalOrangeView::draw(Camera &camera) {
    if (tilted == STRAIGHT) {
        portal.draw(camera, this->getDst(), 0);
    } else if (tilted == LEFT) {
        portal.draw(camera, this->getDst(), 45);
    } else if (tilted == RIGHT) {
        portal.draw(camera, this->getDst(), -45);
    }
}

int PortalOrangeView::getId() const {
    return id;
}
