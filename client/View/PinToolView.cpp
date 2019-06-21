//
// Created by jonathanmedina on 20/06/19.
//

#include <Server/Model/constants.h>
#include "PinToolView.h"

PinToolView::PinToolView(int id, SDL_Texture *texture, Renderer &renderer, int x, int y) :
    View(x,y), id(id),
    pintool(texture, renderer) {
    pintool.setSourceRect(0, 0, 511, 511);
}

void PinToolView::draw(Camera &camera) {
    pintool.draw(camera,this->getDst(), 0);
}

int PinToolView::getId() const {
    return id;
}
