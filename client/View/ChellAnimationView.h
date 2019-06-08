//
// Created by jonathanmedina on 28/05/19.
//

#ifndef SDL_CHELLANIMATIONVIEW_H
#define SDL_CHELLANIMATIONVIEW_H


#include "../ComponentsSDL/AnimatedSprite.h"
#include "View.h"

enum State {standing, runningLeft, runningRight, firing, flying, dying};
class ChellAnimationView : public View {
private:
    int id;
    AnimatedSprite runningRightChell;
    AnimatedSprite standStillChell;
    AnimatedSprite firingChell;
    AnimatedSprite flyingChell;
    AnimatedSprite dyingChell;
    State state;
public:
    ChellAnimationView(int id, SDL_Texture* texture, Renderer& renderer, int x=0, int y=0);
    int getId() const;
    void draw(Camera& camera);
    void setState(State state);
};


#endif //SDL_CHELLANIMATIONVIEW_H
