//
// Created by jonathanmedina on 08/06/19.
//

#include <Server/Model/constants.h>
#include "DiagonalBlockMetalView.h"

DiagonalBlockMetalView::DiagonalBlockMetalView(SDL_Texture *texture, Renderer &renderer, int16_t orientation, int x, int y) : View(x, y), block(texture, renderer), orientation(orientation) {
    block.setSourceRect(323,612,186,186);
}

void DiagonalBlockMetalView::draw(Camera &camera) {
    if (orientation == O_NE) {
        block.draw(camera, this->getDst(), 0);
    } else if (orientation == O_NO) {
        block.draw(camera, this->getDst(), 270);
    } else if (orientation == O_SE) {
        block.draw(camera, this->getDst(), 90);
    } else if (orientation == O_SO) {
        block.draw(camera, this->getDst(), 180);
    }
}
