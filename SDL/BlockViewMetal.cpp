//
// Created by jonathanmedina on 03/06/19.
//

#include "BlockViewMetal.h"

BlockViewMetal::BlockViewMetal(SDL_Texture *texture, Renderer &renderer) : block(texture, renderer){
    block.setSourceRect(1,601,192,192);
}

void BlockViewMetal::draw(Camera &camera) {
    block.draw(camera,this->getDst());
}
