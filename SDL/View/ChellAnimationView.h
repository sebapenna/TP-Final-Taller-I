//
// Created by jonathanmedina on 28/05/19.
//

#ifndef SDL_CHELLANIMATIONVIEW_H
#define SDL_CHELLANIMATIONVIEW_H


#include "AnimatedSprite.h"
#include "View.h"


class ChellAnimationView : public View {
    enum State {standing, runningLeft, runningRight, firing};
private:
    AnimatedSprite runningRightChell;
    AnimatedSprite standStillChell;
    AnimatedSprite firingChell;
    State state;
public:
    ChellAnimationView(SDL_Texture* texture, Renderer& renderer, int x=0, int y=0);
    void draw(Camera& camera);
    void moveToTheLeft(int x);
    void moveToTheRight(int x);
    void stand();
    void fire();
};


#endif //SDL_CHELLANIMATIONVIEW_H
