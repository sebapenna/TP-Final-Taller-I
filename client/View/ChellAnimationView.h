//
// Created by jonathanmedina on 28/05/19.
//

#ifndef SDL_CHELLANIMATIONVIEW_H
#define SDL_CHELLANIMATIONVIEW_H


#include "../ComponentsSDL/AnimatedSprite.h"
#include "View.h"

enum ChellState {standing, runningLeft, runningRight, firing, flying, dying, winning};
enum ChellIsTilted {TILTEDLEFT, TILTEDRIGHT, NO};
class ChellAnimationView : public View {
private:
    int id;
    AnimatedSprite runningRightChell;
    AnimatedSprite standStillChell;
    AnimatedSprite firingChell;
    AnimatedSprite flyingChell;
    AnimatedSprite dyingChell;
    AnimatedSprite winningChell;
    ChellState state;
    ChellIsTilted tiltedState;

    double getAngle() const;
public:
    ChellAnimationView(int id, SDL_Texture* dyingTexture, SDL_Texture* firingTexture,
            SDL_Texture* flyingTexture, SDL_Texture* restingTexture,
            SDL_Texture* runningTexture, SDL_Texture* winningTexture, Renderer& renderer, int x=0, int y=0);
    int getId() const;
    void draw(Camera& camera);
    void setState(ChellState state);
    void setTiltedState(ChellIsTilted state);
    bool isDead();
    bool isDying();
    ChellState getState() const;
};


#endif //SDL_CHELLANIMATIONVIEW_H
