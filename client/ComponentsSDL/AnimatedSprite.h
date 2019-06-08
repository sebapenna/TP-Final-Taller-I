//
// Created by jonathanmedina on 26/05/19.
//

#ifndef SDL_ANIMATEDSPRITE_H
#define SDL_ANIMATEDSPRITE_H


#include "Sprite.h"
#define DEFAULT_TIME_PER_SPRITE 4

enum AnimationState {onRepeat, oneTime};
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
    AnimationState animationState;


public:
    AnimatedSprite(SDL_Texture* texture, Renderer &renderer,
                   int width, int height,
                   int startX, int startY,
                   int totalColumns, int amountSprites, int offSetX, int offSetY, AnimationState animationState);
    void moveNextSprite();
    void drawMovingSprite(Camera& camera, SDL_Rect* dstRect);
    void drawMovingSprite(Camera& camera, SDL_Rect* dstRect, SDL_RendererFlip flip);
    void setTimePerSprite(Uint32 t);
    void reset();
};


#endif //SDL_ANIMATEDSPRITE_H
