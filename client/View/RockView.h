//
// Created by jonathanmedina on 08/06/19.
//

#ifndef PORTAL_ROCKVIEW_H
#define PORTAL_ROCKVIEW_H


#include <client/ComponentsSDL/Sprite.h>
#include "View.h"

class RockView : public View {
private:
    Sprite rock;
public:
    RockView(SDL_Texture* texture, Renderer& renderer, int  x = 0, int y = 0);
    void draw(Camera& camera);
};


#endif //PORTAL_ROCKVIEW_H
