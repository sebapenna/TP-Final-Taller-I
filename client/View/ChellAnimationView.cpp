//
// Created by jonathanmedina on 28/05/19.
//

#include "ChellAnimationView.h"

ChellAnimationView::ChellAnimationView(int id, SDL_Texture* texture, Renderer& renderer, int x, int y) : id(id),
View(x, y),
runningRightChell(texture, renderer, 201, 220, 1, 3983, 12, 12, 1, 0),
standStillChell(texture, renderer, 122, 222, 1, 2080, 7, 7, 1, 0),
firingChell(texture, renderer, 190, 212, 1, 2546, 5, 5, 1, 0),state(standing) {
}

void ChellAnimationView::draw(Camera& camera) {
    if (state == standing) {
        standStillChell.drawMovingSprite(camera, this->getDst());
    } else if (state == runningLeft) {
        runningRightChell.drawMovingSprite(camera, this->getDst(), SDL_FLIP_HORIZONTAL);
    } else if (state == runningRight) {
        runningRightChell.drawMovingSprite(camera, this->getDst());
    } else if (state == firing) {
        firingChell.drawMovingSprite(camera, this->getDst());
    }
}

void ChellAnimationView::moveToTheLeft(int x) {
    SDL_Rect* nueva_pos = this->getDst();
    this->setDestRect(nueva_pos->x - x, nueva_pos->y, nueva_pos->w, nueva_pos->h);
    this->state = runningLeft;
}

void ChellAnimationView::moveToTheRight(int x) {
    SDL_Rect* nueva_pos = this->getDst();
    this->setDestRect(nueva_pos->x + x, nueva_pos->y, nueva_pos->w, nueva_pos->h);
    this->state = runningRight;
}

void ChellAnimationView::stand() {
    this->state = State::standing;
}

void ChellAnimationView::fire() {
    this->state = State::firing;
}

int ChellAnimationView::getId() const {
    return id;
}
