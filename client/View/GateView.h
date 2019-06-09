//
// Created by jonathanmedina on 08/06/19.
//

#ifndef PORTAL_GATEVIEW_H
#define PORTAL_GATEVIEW_H


#include <client/ComponentsSDL/Sprite.h>
#include <client/ComponentsSDL/AnimatedSprite.h>
#include "View.h"

enum GateState {open, closed, isClosingBack};
class GateView : public View {
private:
    int id;
    Sprite closedGate;
    AnimatedSprite gate;
    GateState state;
public:
    GateView(int id, SDL_Texture* texture, Renderer& renderer, int  x = 0, int y = 0);
    int getId() const;
    void draw(Camera& camera);
    void close();
    void open();
};


#endif //PORTAL_GATEVIEW_H
