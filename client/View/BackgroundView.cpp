//
// Created by jonathanmedina on 11/06/19.
//

#include "BackgroundView.h"


BackgroundView::BackgroundView(SDL_Texture *texture, Renderer &renderer, int x, int y) : View(x, y), background(texture, renderer), renderer(renderer) {
    background.setSourceRect(0, 0, 1980, 1024);
}

void BackgroundView::draw(Camera& camera) {
    renderer.copyTexture(background.getTexture());
}
