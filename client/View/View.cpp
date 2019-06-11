//
// Created by jonathanmedina on 02/06/19.
//

#include "View.h"

#define METERS_TO_PIXELS_CONVERSION 1.1
View::View(int x, int y) : position(x, y) {
}

SDL_Rect* View::getDst() {
    return &dstSrc;
}


// Ahora x, y es izq, inferior
void View::setDestRect(int x, int y, int w, int h) {
    position.set(x + w / 2, y - h / 2); // -h/2
    dstSrc.x = x;
    dstSrc.y = y-h; //  -h despues paasa a izquierda inferior
    dstSrc.w = w;
    dstSrc.h = h;
}

void View::setPosition(Position &position) {
    dstSrc.x = position.getX() - this->getDst()->w/2;
    dstSrc.y = position.getY() - this->getDst()->h/2;
    //this->position.set(position.getX() + dstSrc.w/2, position.getY() - dstSrc.h/2);
    this->position = position;
}

Position &View::getPosition() {
    return position;
}

int View::convertMetersToPixels(int meters) {
    return meters*METERS_TO_PIXELS_CONVERSION;
}

