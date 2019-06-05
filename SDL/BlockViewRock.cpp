//
// Created by jonathanmedina on 03/06/19.
//

#include "BlockViewRock.h"

BlockViewRock::BlockViewRock(SDL_Texture *texture, Renderer &renderer, int x, int y) : View(x, y), block(texture, renderer) {
    block.setSourceRect(1,23,128,128);
}

void BlockViewRock::draw(Camera &camera) {
    block.draw(camera,this->getDst());
}
