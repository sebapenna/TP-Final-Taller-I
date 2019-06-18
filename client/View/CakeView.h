//
// Created by jonathanmedina on 17/06/19.
//

#ifndef PORTAL_CAKEVIEW_H
#define PORTAL_CAKEVIEW_H


#include <client/ComponentsSDL/AnimatedSprite.h>
#include "View.h"

class CakeView : public View {
private:
    AnimatedSprite cake;
public:
    CakeView(SDL_Texture* texture, Renderer& renderer, int x = 0, int y = 0);
    void draw(Camera& camera);
};


#endif //PORTAL_CAKEVIEW_H
