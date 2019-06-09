//
// Created by jonathanmedina on 02/06/19.
//

#include "View.h"

SDL_Rect* View::getDst() {
    return &dstSrc;
}

// Ahora x, y es izq, superior
void View::setDestRect(int x, int y, int w, int h) {
    position.set(x + w / 2, y + h / 2); // -h/2
    dstSrc.x = x;
    dstSrc.y = y; //  -h despues paasa a izquierda inferior
    dstSrc.w = w;
    dstSrc.h = h;
}

View::View(int x, int y) : position(x, y) {
}

Position &View::getPosition() {
    return position;
}

void View::setPosition(Position &position) {
    dstSrc.x = position.getX();
    dstSrc.y = position.getY();
    this->position.set(position.getX() + dstSrc.w/2, position.getY()+ dstSrc.h/2);
    //this->position = position;
}