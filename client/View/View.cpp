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

void View::setDestRect(int x, int y, int radius) {
    dstSrc.x = convertMetersToPixelsPos(x - radius);
    dstSrc.y = convertMetersToPixelsPos(-y - radius);
    dstSrc.w = convertMetersToPixelsPos(radius * 2);
    dstSrc.h = convertMetersToPixelsPos(radius * 2);
}
// Ahora x, y es izq, inferior
void View::setDestRect(int x, int y, int w, int h) {
    // MULTIPLICAR POR EL ANCHO DE LA PANTALLA. Y EL ALTO
    // MULTIPLICAR POR ANCHO Y DIVIDIR POR UNA CONSTANTE DE AJUSTE.
    position.set(convertMetersToPixelsPos(x + w / 2), convertMetersToPixelsPos(-y - h)); // -h/2
    dstSrc.x = convertMetersToPixelsPos(x);
    dstSrc.y = convertMetersToPixelsPos(-y-h);
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
    // TENGO DOS FUNCIONES, SI NO ESTA
    // return meters * h * METERS_TO_PIXELS_POS
    // min(meters * h * METERS_TO_PIXELS_POS, meters * w * METERS_TO_PIXELS_POS)
    return meters*METERS_TO_PIXELS_POS;
}

/*int View::convertMetersToPixelsTam(int meters) {
    return meters*METERS_TO_PIXELS_TAM;
}*/

