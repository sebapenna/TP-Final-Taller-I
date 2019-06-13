//
// Created by jonathanmedina on 08/06/19.
//

#ifndef PORTAL_ENERGYBARVIEW_H
#define PORTAL_ENERGYBARVIEW_H


#include <client/ComponentsSDL/Sprite.h>
#include "View.h"

class EnergyBarView : public View {
private:
    Sprite bar;
public:
    EnergyBarView(SDL_Texture* texture, Renderer& renderer, int x = 0, int y = 0);
    void draw(Camera& camera);
};


#endif //PORTAL_ENERGYBARVIEW_H
