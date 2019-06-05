//
// Created by jonathanmedina on 03/06/19.
//

#ifndef SDL_BLOCKVIEWMETAL_H
#define SDL_BLOCKVIEWMETAL_H


#include "../Sprite.h"

class BlockViewMetal : public View{
private:
    Sprite block;
public:
    BlockViewMetal(SDL_Texture* texture, Renderer& renderer, int x = 0, int y = 0);
    void draw(Camera& camera);
};


#endif //SDL_BLOCKVIEWMETAL_H
