//
// Created by jonathanmedina on 03/06/19.
//

#include "BlockMetalView.h"

BlockMetalView::BlockMetalView(SDL_Texture *texture, Renderer &renderer, int x, int y) : View(x, y), block(texture, renderer) {
    block.setSourceRect(1,601,192,192);
}

void BlockMetalView::draw(Camera &camera) {
    block.draw(camera,this->getDst());
}
