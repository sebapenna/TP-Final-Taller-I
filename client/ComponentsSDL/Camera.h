#ifndef SDL_CAMERA_H
#define SDL_CAMERA_H

#include <SDL2/SDL_rect.h>
#include "../View/View.h"
#include "Renderer.h"
#include "Position.h"

class Camera {
private:
    Position& position;
    int w;
    int h;
    int convertPixelsToMeters(int var);
public:
    Camera(int w, int h, Position& position);
    void draw(SDL_Texture* texture, SDL_Rect* srcRect,SDL_Rect* dstRect, Renderer& renderer, double angle=0, SDL_RendererFlip flip=SDL_FLIP_NONE);
    bool isInCamera(SDL_Rect* dstRect);
    Position& getPosition();

    void obtainXY(int &x, int &y, int x_m, int y_m, Renderer& renderer);
};


#endif //SDL_CAMERA_H
