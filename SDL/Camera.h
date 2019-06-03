#ifndef SDL_CAMERA_H
#define SDL_CAMERA_H

#include <SDL2/SDL_rect.h>
#include "View.h"
#include "Renderer.h"

class Camera {
private:
    SDL_Rect camera_location;
public:
    Camera(int x, int y, int w, int h);

    void draw(SDL_Texture* texture, SDL_Rect* srcRect,SDL_Rect* dstRect, Renderer& renderer, SDL_RendererFlip flip=SDL_FLIP_NONE);
    void moveCameraLeft();
    void moveCameraRight();
    void moveCameraUp();
    void moveCameraDown();
    bool isInCamera(SDL_Rect* dstRect);
};


#endif //SDL_CAMERA_H
