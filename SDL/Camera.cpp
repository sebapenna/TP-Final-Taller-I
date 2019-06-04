//
// Created by jonathanmedina on 02/06/19.
//

#include "Camera.h"

#define PIXELS_MOVE_CAMERA 10

Camera::Camera(int w, int h, SDL_Rect* chell_pos) : chell_pos(chell_pos) {
    camera_location.x = chell_pos->x - w/2;
    camera_location.y = chell_pos->y - h/2;
    camera_location.w = w;
    camera_location.h = h;
}

void
Camera::draw(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect, Renderer &renderer, SDL_RendererFlip flip) {
    camera_location.x = chell_pos->x - camera_location.w/2;
    camera_location.y = chell_pos->y - camera_location.h/2;
    SDL_Rect to_draw;
    to_draw.x =  dstRect->x - camera_location.x;
    to_draw.y =  dstRect->y - camera_location.y;
    to_draw.w = dstRect->w;
    to_draw.h = dstRect->h;
    renderer.copyTexture(texture, srcRect, &to_draw, 0, NULL, flip);
}


void Camera::moveCameraLeft() {
    camera_location.x-=PIXELS_MOVE_CAMERA;
}

void Camera::moveCameraRight() {
    camera_location.x+=PIXELS_MOVE_CAMERA;
}

void Camera::moveCameraUp() {
    camera_location.y-=PIXELS_MOVE_CAMERA;
}

void Camera::moveCameraDown() {
    camera_location.y+=PIXELS_MOVE_CAMERA;
}

bool Camera::isInCamera(SDL_Rect* dstRect) {
    if (dstRect->x + dstRect->w < camera_location.x) return false;
    if (dstRect->x > abs(camera_location.x) + camera_location.w) return false;
    if (dstRect->y + dstRect->h < camera_location.y) return false;
    if (dstRect->y > abs(camera_location.y) + camera_location.h) return false;
    return true;
}
