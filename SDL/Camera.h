#ifndef SDL_CAMERA_H
#define SDL_CAMERA_H

#include <SDL2/SDL_rect.h>
#include "View.h"
#include "Renderer.h"
#include "Position.h"

class Camera {
private:
    Position& position;
    int w;
    int h;
    //SDL_Rect* chell_pos;
public:
    Camera(int w, int h, Position& position);
    void draw(SDL_Texture* texture, SDL_Rect* srcRect,SDL_Rect* dstRect, Renderer& renderer, SDL_RendererFlip flip=SDL_FLIP_NONE);
    bool isInCamera(SDL_Rect* dstRect);
};


#endif //SDL_CAMERA_H
