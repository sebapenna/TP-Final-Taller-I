//
// Created by jonathanmedina on 13/06/19.
//

#ifndef PORTAL_ENERGYTRANSMITTERVIEW_H
#define PORTAL_ENERGYTRANSMITTERVIEW_H


#include <client/ComponentsSDL/AnimatedSprite.h>
#include "View.h"

enum EnergyTransmitterState {transmiting, notTransmiting};
class EnergyTransmitterView : public View {
private:
    int id;
    Sprite notTransmiting;
    AnimatedSprite transmiteAnimation;
    int16_t orientation;
    EnergyTransmitterState state;
    int angle;
    void setAngle();
public:
    EnergyTransmitterView(int id, SDL_Texture* texture, Renderer& renderer, int16_t orientation, int  x = 0, int y = 0);
    int getId() const;
    void draw(Camera& camera);
    void transmite();
};


#endif //PORTAL_ENERGYTRANSMITTERVIEW_H
