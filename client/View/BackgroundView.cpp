//
// Created by jonathanmedina on 11/06/19.
//

#include "BackgroundView.h"


BackgroundView::BackgroundView(SDL_Texture *texture, Renderer &renderer, int x, int y) : View(x, y), background(texture, renderer) {
    background.setSourceRect(0, 0, 1980, 1024);
}

void BackgroundView::draw(Camera &camera) {
    this->setPosition(camera.getPosition());
    this->setDestRect(this->getPosition().getX()- this->getDst()->w/2, this->getPosition().getY() + this->getDst()->h/2, this->getDst()->w, this->getDst()->h);
    background.draw(camera,this->getDst());
}
