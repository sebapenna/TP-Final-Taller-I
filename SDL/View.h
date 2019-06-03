//
// Created by jonathanmedina on 02/06/19.
//

#ifndef SDL_VIEW_H
#define SDL_VIEW_H


#include <SDL2/SDL_rect.h>
#include "Camera.h"

class Camera;

class View {
private:
    SDL_Rect dstSrc;
public:
    SDL_Rect* getDst();
    void setDestRect(int x, int y, int w, int h);
    virtual void draw(Camera& camera) = 0;
};


#endif //SDL_VIEW_H
