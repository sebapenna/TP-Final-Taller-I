//
// Created by jonathanmedina on 02/06/19.
//

#ifndef SDL_WORLDVIEW_H
#define SDL_WORLDVIEW_H


#include "ComponentsSDL/Camera.h"
#include "View/ChellAnimationView.h"
#include <vector>
#include <map>
#include <client/View/GateView.h>
#include <client/View/ButtonView.h>
#include <client/View/RockView.h>

class WorldView {
private:
    std::vector<View*> views;
    std::map<int, ChellAnimationView*> chells;
    std::map<int, GateView*> gates;
    std::map<int, ButtonView*> buttons;
    std::map<int, RockView*> rocks;

    Camera* camera;
public:
    WorldView();
    ~WorldView();
    void setCamara(int16_t id, int w, int h);
    void draw();
    void addView(View* view);
    void addGates(GateView* gate);
    void openGate(int16_t id);
    void closeGate(int16_t id);
    void addButton(ButtonView* button);
    void activateButton(int16_t id);
    void deactivateButton(int16_t id);
    void addChell(ChellAnimationView* chell, Position& position);
    void setChellState(int16_t id, ChellState state);
    void addRock(RockView* rock);
};


#endif //SDL_WORLDVIEW_H
