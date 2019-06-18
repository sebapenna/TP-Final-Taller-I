//
// Created by jonathanmedina on 17/06/19.
//

#include "CakeView.h"

CakeView::CakeView(SDL_Texture *texture, Renderer &renderer, int x, int y)  :
        View(x, y),
        cake(texture, renderer, 75, 109, 12, 134, 5, 5, 15, 0, AnimationState::onRepeat){
}

void CakeView::draw(Camera &camera) {
    cake.drawMovingSprite(camera, this->getDst());
}
