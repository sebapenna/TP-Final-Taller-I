//
// Created by jonathanmedina on 03/06/19.
//

#ifndef SDL_BLOCKVIEWROCK_H
#define SDL_BLOCKVIEWROCK_H


#include "Sprite.h"

class BlockViewRock : public View{
private:
    Sprite block;
public:
    BlockViewRock(SDL_Texture* texture, Renderer& renderer, int  x = 0, int y = 0);
    void draw(Camera& camera);
};


#endif //SDL_BLOCKVIEWROCK_H
