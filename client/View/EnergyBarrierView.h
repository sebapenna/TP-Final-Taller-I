//
// Created by jonathanmedina on 08/06/19.
//

#ifndef PORTAL_ENERGYBARRIERVIEW_H
#define PORTAL_ENERGYBARRIERVIEW_H


#include <client/ComponentsSDL/Sprite.h>
#include "View.h"

class EnergyBarrierView : public View {
private:
    Sprite bar;
public:
    EnergyBarrierView(SDL_Texture* texture, Renderer& renderer, int x = 0, int y = 0);
    void draw(Camera& camera);
};


#endif //PORTAL_ENERGYBARRIERVIEW_H
