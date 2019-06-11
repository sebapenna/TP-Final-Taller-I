//
// Created by jonathanmedina on 02/06/19.
//

#include "View.h"

#define METERS_TO_PIXELS_TAM 30
#define METERS_TO_PIXELS_POS 30
View::View(int x, int y) : position(x, y) {
}

SDL_Rect* View::getDst() {
    return &dstSrc;
}


// Ahora x, y es izq, inferior
void View::setDestRect(int x, int y, int w, int h) {
    position.set(convertMetersToPixelsPos(x + w / 2), convertMetersToPixelsPos(-y - h)); // -h/2
    dstSrc.x = convertMetersToPixelsPos(x);
    dstSrc.y = convertMetersToPixelsPos(-y-h); //  -h despues paasa a izquierda inferior
    dstSrc.w = convertMetersToPixelsPos(w);
    dstSrc.h = convertMetersToPixelsPos(h);
}

void View::setPosition(Position &position) {
    dstSrc.x = position.getX() - this->getDst()->w/2;
    dstSrc.y = position.getY();
    //this->position.set(position.getX() + dstSrc.w/2, position.getY() - dstSrc.h/2);
    this->position = position;
}

Position &View::getPosition() {
    return position;
}

int View::convertMetersToPixelsPos(int meters) {
    return meters*METERS_TO_PIXELS_POS;
}

/*int View::convertMetersToPixelsTam(int meters) {
    return meters*METERS_TO_PIXELS_TAM;
}*/

