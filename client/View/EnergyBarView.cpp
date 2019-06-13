//
// Created by jonathanmedina on 08/06/19.
//

#include "EnergyBarView.h"

EnergyBarView::EnergyBarView(SDL_Texture *texture, Renderer &renderer, int x, int y) : View(x, y), bar(texture, renderer){
    bar.setSourceRect(7, 1741, 1, 1);
}

void EnergyBarView::draw(Camera &camera) {
    bar.draw(camera,this->getDst());
}
