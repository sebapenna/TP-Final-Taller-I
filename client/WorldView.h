//
// Created by jonathanmedina on 02/06/19.
//

#ifndef SDL_WORLDVIEW_H
#define SDL_WORLDVIEW_H


#include "ComponentsSDL/Camera.h"
#include "View/ChellAnimationView.h"
#include "common/ProtocolTranslator/FakeChellNewPosition.h"
#include <vector>
#include <map>

class WorldView {
private:
    Camera& camera;
    std::vector<View*> views;
    std::map<int, ChellAnimationView*> chells;
public:
    WorldView(Camera& camera);
    void moveCameraLeft();
    void moveCameraRight();
    void moveCameraUp();
    void moveCameraDown();
    void draw();
    void addView(View* view);
    void addChell(ChellAnimationView* chell, Position& position);
};


#endif //SDL_WORLDVIEW_H
