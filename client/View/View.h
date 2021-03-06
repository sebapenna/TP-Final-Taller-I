//
// Created by jonathanmedina on 02/06/19.
//

#ifndef SDL_VIEW_H
#define SDL_VIEW_H


#include <SDL2/SDL_rect.h>
#include "../ComponentsSDL/Camera.h"
#include "../ComponentsSDL/Position.h"

class Camera;

// This class holds all the information
// To know where the object is positionated in the world
class View {
private:
    SDL_Rect dstSrc;
    Position position;
    int convertMetersToPixelsPos(int meters);
public:
    View(int x, int y);
    SDL_Rect* getDst();
    void setDestRect(int x, int y, int radius);
    void setDestRect(int x, int y, int w, int h);
    void setPosition(Position& position);
    virtual void draw(Camera& camera) = 0;
    Position& getPosition();

};


#endif //SDL_VIEW_H
