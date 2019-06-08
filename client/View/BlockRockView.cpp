//
// Created by jonathanmedina on 03/06/19.
//

#include "BlockRockView.h"

BlockRockView::BlockRockView(SDL_Texture *texture, Renderer &renderer, int x, int y) : View(x, y), block(texture, renderer) {
    block.setSourceRect(1,23,128,128);
}

void BlockRockView::draw(Camera &camera) {
    block.draw(camera,this->getDst());
}
