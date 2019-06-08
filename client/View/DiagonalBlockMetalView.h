//
// Created by jonathanmedina on 08/06/19.
//

#ifndef PORTAL_DIAGONALBLOCKMETALVIEW_H
#define PORTAL_DIAGONALBLOCKMETALVIEW_H


#include <client/ComponentsSDL/Sprite.h>
#include "View.h"

class DiagonalBlockMetalView : public View {
private:
    Sprite block;
public:
    DiagonalBlockMetalView(SDL_Texture* texture, Renderer& renderer, int x = 0, int y = 0);
    void draw(Camera& camera);
};


#endif //PORTAL_DIAGONALBLOCKMETALVIEW_H
