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
        if (camera.isInCamera(chell->getDst())) {
            chell->draw(camera);
        }
    }
}

void WorldView::addView(View* view) {
    views.push_back(view);
}

void WorldView::addChell(ChellAnimationView* chell) {
    chells.push_back(chell);
}

// Como actualizo un objeto en particular asi?. Tengo un std::map con el id del objeto? a actualizar.

