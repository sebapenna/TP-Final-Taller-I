//
// Created by jonathanmedina on 02/06/19.
//

#include "WorldView.h"

WorldView::WorldView(Camera& camera) : camera(camera) {
}

void WorldView::draw() {
    for(auto const& view: views) {
        if (camera.isInCamera(view->getDst())) {
            view->draw(camera);
        }
    }
    for(auto const& chell: chells) {
        if (camera.isInCamera(chell.second->getDst())) {
            chell.second->draw(camera);
        }
    }
}

void WorldView::addView(View* view) {
    views.push_back(view);
}

void WorldView::addChell(ChellAnimationView* chell, Position& position, State state) {
    if (chells.count(chell->getId())) {
        ChellAnimationView* chellView = chells[chell->getId()];
        chellView->setPosition(position);
        chellView->setState(state);
    } else {
        chells[chell->getId()] = chell;
        chell->setDestRect(position.getX(), position.getY(), 201, 220 );
        chell->setState(state);
    }

}

// Como actualizo un objeto en particular asi?. Tengo un std::map con el id del objeto? a actualizar.

