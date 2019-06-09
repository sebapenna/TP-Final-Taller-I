//
// Created by jonathanmedina on 02/06/19.
//

#ifndef SDL_WORLDVIEW_H
#define SDL_WORLDVIEW_H


#include "ComponentsSDL/Camera.h"
#include "View/ChellAnimationView.h"
#include <vector>
#include <map>
#include <client/View/GatesView.h>

class WorldView {
private:
    std::vector<View*> views;
    std::map<int, ChellAnimationView*> chells;
    std::map<int, GatesView*> gates;
    Camera* camera;
public:
    WorldView();
    ~WorldView();
    void setCamara(int16_t id, int w, int h);
    void draw();
    void addView(View* view);
    void addGates(GatesView* gate);
    void openGate(int16_t id);
    void closeGate(int16_t id);
    void addChell(ChellAnimationView* chell, Position& position);
    void setChellState(int16_t id, ChellState state);
};


#endif //SDL_WORLDVIEW_H
