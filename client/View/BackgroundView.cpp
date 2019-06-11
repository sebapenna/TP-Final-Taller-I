//
// Created by jonathanmedina on 11/06/19.
//

#include "BackgroundView.h"


BackgroundView::BackgroundView(SDL_Texture *texture, Renderer &renderer, int x, int y) : View(x, y), background(texture, renderer) {
    background.setSourceRect(0, 0, 800, 30);
}

void BackgroundView::draw(Camera &camera) {
    background.draw(camera,this->getDst());
}
