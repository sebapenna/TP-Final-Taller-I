//
// Created by jonathanmedina on 08/06/19.
//

#include "DiagonalBlockMetalView.h"

DiagonalBlockMetalView::DiagonalBlockMetalView(SDL_Texture *texture, Renderer &renderer, int x, int y) : View(x, y), block(texture, renderer) {
    block.setSourceRect(323,612,186,186);
}

void DiagonalBlockMetalView::draw(Camera &camera) {
    block.draw(camera,this->getDst());
}
