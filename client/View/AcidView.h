//
// Created by jonathanmedina on 08/06/19.
//

#ifndef PORTAL_ACIDVIEW_H
#define PORTAL_ACIDVIEW_H


#include <client/ComponentsSDL/AnimatedSprite.h>
#include "View.h"

class AcidView : public View {
private:
    AnimatedSprite acid;
public:
    AcidView(SDL_Texture* texture, Renderer& renderer, int x = 0, int y = 0);
    void draw(Camera& camera);
};


#endif //PORTAL_ACIDVIEW_H
