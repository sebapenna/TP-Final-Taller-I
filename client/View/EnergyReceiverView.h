//
// Created by jonathanmedina on 13/06/19.
//

#ifndef PORTAL_ENERGYRECEIVERVIEW_H
#define PORTAL_ENERGYRECEIVERVIEW_H


#include <client/ComponentsSDL/AnimatedSprite.h>
#include "View.h"

enum EnergyReceiverState {enable,disable};
class EnergyReceiverView : public View {
private:
    int id;
    Sprite energyReceiverSprite;
    AnimatedSprite energyReceiverAnimation;
    EnergyReceiverState state;
public:
    EnergyReceiverView(int id, SDL_Texture* texture, Renderer& renderer, int x = 0, int y = 0);
    void draw(Camera& camera);
    void activate();
    int getId() const;
};


#endif //PORTAL_ENERGYRECEIVERVIEW_H
