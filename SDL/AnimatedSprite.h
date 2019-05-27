//
// Created by jonathanmedina on 26/05/19.
//

#ifndef SDL_ANIMATEDSPRITE_H
#define SDL_ANIMATEDSPRITE_H


#include "Sprite.h"
#define DEFAULT_TIME_PER_SPRITE 4

class AnimatedSprite : public Sprite{
private:
    int width;
    int height;
    int startX;
    int startY;
    int totalColumns; // Empieza en 1
    int amountSprites; // Empieza en 1
    int offSetX;
    int offSetY;
    int currentTime;
    int timePerSprite;
    int currentSprite;
    int i; // The offset for the images
    int j;


public:
    AnimatedSprite(const std::string &filename, Renderer &renderer,
                   int width, int height,
                   int startX, int startY,
                   int totalColumns, int amountSprites, int finalX, int finalY,
                   int finalWidth, int finalHeight, int offSetX, int offSetY);
    void moveNextSprite();
    void drawMovingSprite();
    void setTimePerSprite(Uint32 t);
    void reset();
};


#endif //SDL_ANIMATEDSPRITE_H
