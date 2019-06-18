//
// Created by jonathanmedina on 18/06/19.
//

#ifndef PORTAL_ENERGYBALLVIEW_H
#define PORTAL_ENERGYBALLVIEW_H


#include <client/ComponentsSDL/AnimatedSprite.h>
#include "View.h"

class EnergyBallView : public View {
private:
    int id;
    AnimatedSprite ball;
public:
    EnergyBallView(int id, SDL_Texture* texture, Renderer& renderer, int x = 0, int y = 0);

    void draw(Camera& camera);

    int getId() const;
};


#endif //PORTAL_ENERGYBALLVIEW_H
