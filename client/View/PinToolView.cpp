//
// Created by jonathanmedina on 20/06/19.
//

#include <Server/Model/constants.h>
#include "PinToolView.h"

PinToolView::PinToolView(int id, SDL_Texture *texture, Renderer &renderer, int16_t tilted, int x, int y) :
    View(x,y), id(id),
    pintool(texture, renderer), tilted(tilted){
    pintool.setSourceRect(0, 0, 511, 511);
}

void PinToolView::draw(Camera &camera) {
    if (tilted == STRAIGHT) {
        pintool.draw(camera,this->getDst(), 0);
    } else if (tilted == LEFT) {
        pintool.draw(camera,this->getDst(), 45);
    } else if (tilted == RIGHT) {
        pintool.draw(camera,this->getDst(), -45);
    }
}

int PinToolView::getId() const {
    return id;
}
