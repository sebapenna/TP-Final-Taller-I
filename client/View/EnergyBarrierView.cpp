//
// Created by jonathanmedina on 08/06/19.
//

#include "EnergyBarrierView.h"

EnergyBarrierView::EnergyBarrierView(SDL_Texture *texture, Renderer &renderer, int x, int y) : View(x, y), bar(texture, renderer){
    bar.setSourceRect(7, 1741, 1, 1);
}

void EnergyBarrierView::draw(Camera &camera) {
    bar.draw(camera,this->getDst());
}
