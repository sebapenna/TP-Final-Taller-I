//
// Created by jonathanmedina on 02/06/19.
//

#include "View.h"

SDL_Rect* View::getDst() {
    return &dstSrc;
}

void View::setDestRect(int x, int y, int w, int h) {
    dstSrc.x = x;
    dstSrc.y = y;
    dstSrc.w = w;
    dstSrc.h = h;
}
