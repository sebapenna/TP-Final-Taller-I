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
#include <memory>
#include <client/View/BackgroundView.h>

class WorldView {
private:
    std::vector<std::shared_ptr<View>> views;
    std::map<int, std::shared_ptr<ChellAnimationView>> chells;
    std::map<int, std::shared_ptr<GateView>> gates;
    std::map<int, std::shared_ptr<ButtonView>> buttons;
    std::map<int, std::shared_ptr<RockView>> rocks;
    std::shared_ptr<BackgroundView> background;
    Camera* camera;
public:
    WorldView();
    ~WorldView();
    void setCamara(int16_t id, int w, int h);
    void draw();
    void addView(std::shared_ptr<View> view);
    void addGates(std::shared_ptr<GateView> gate);
    void openGate(int16_t id);
    void closeGate(int16_t id);
    void addButton(std::shared_ptr<ButtonView>& button);
    void activateButton(int16_t id);
    void deactivateButton(int16_t id);
    void addChell(std::shared_ptr<ChellAnimationView>& chell);
    void setChellState(int16_t id, ChellState state);
    void makeChellTiltedLeft(int16_t id);
    void makeChellTiltedRight(int16_t id);
    void makeChellNotTilted(int16_t id);
    void addRock(std::shared_ptr<RockView> rock);
    void setBackground(std::shared_ptr<BackgroundView>& background);
};


#endif //SDL_WORLDVIEW_H
