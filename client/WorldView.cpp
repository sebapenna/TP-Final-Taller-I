//
// Created by jonathanmedina on 02/06/19.
//

#include "WorldView.h"

WorldView::WorldView() : camera(nullptr){}

void WorldView::draw() {
    if (camera == nullptr) return;
    for(auto const& view: views) {
        if (camera->isInCamera(view->getDst())) {
            view->draw(*camera);
        }
    }
    for(auto const& chell: chells) {
        if (camera->isInCamera(chell.second->getDst())) {
            chell.second->draw(*camera);
        }
    }
}

void WorldView::addView(View* view) {
    views.push_back(view);
}

void WorldView::addChell(ChellAnimationView* chell, Position& position) {
    if (chells.count(chell->getId())) {
        ChellAnimationView* chellView = chells[chell->getId()];
        chellView->setPosition(position);
    } else {
        chells[chell->getId()] = chell;
        chell->setDestRect(position.getX(), position.getY(), 201, 220 );
    }
}

void WorldView::setChellState(int16_t id, State state) {
    ChellAnimationView* chell = chells[id];
    chell->setState(state);
}

void WorldView::setCamara(Camera& camera) {
    this->camera = &camera;
}
