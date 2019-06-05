//
// Created by jonathanmedina on 02/06/19.
//

#include "Camera.h"
#include "Position.h"

#define PIXELS_MOVE_CAMERA 10

// METER UN CHELL OBSERVER POSITION.
// Y LE PIDA LA POSICION A CHELL.

// CLASE POSITION QUE TENGA EL X,Y DE CHELL.

Camera::Camera(int w, int h, Position& position) : position(position), w(w), h(h) {
}
void
Camera::draw(SDL_Texture *texture, SDL_Rect *srcRect,
        SDL_Rect *dstRect, Renderer &renderer, SDL_RendererFlip flip) {
    SDL_Rect to_draw;
    to_draw.x = dstRect->x - position.getX() + this->w / 2;
    to_draw.y = dstRect->y - position.getY() + this->h / 2;
    to_draw.w = dstRect->w;
    to_draw.h = dstRect->h;
    renderer.copyTexture(texture, srcRect, &to_draw, 0, NULL, flip);
}

bool Camera::isInCamera(SDL_Rect* dstRect) {
    if (dstRect->x + dstRect->w < position.getX() - this->w/2) return false;
    if (dstRect->x > abs(position.getX()) + this->w) return false;
    if (dstRect->y + dstRect->h < position.getY() - this->h/2) return false;
    if (dstRect->y > abs(position.getY()) + this->h) return false;
    return true;
}
