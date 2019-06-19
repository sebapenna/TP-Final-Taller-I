//
// Created by jonathanmedina on 02/06/19.
//

#ifndef SDL_WORLDVIEW_H
#define SDL_WORLDVIEW_H


#include <vector>
#include <map>
#include <memory>
#include "ComponentsSDL/Camera.h"
#include "View/ChellAnimationView.h"
#include <client/View/GateView.h>
#include <client/View/ButtonView.h>
#include <client/View/RockView.h>
#include <client/View/BackgroundView.h>
#include <client/View/EnergyReceiverView.h>
#include <client/View/CakeView.h>
#include <client/View/EnergyTransmitterView.h>
#include <client/View/EnergyBallView.h>

class WorldView {
private:
    std::vector<std::shared_ptr<View>> views;
    std::map<int, std::shared_ptr<ChellAnimationView>> chells;
    std::map<int, std::shared_ptr<GateView>> gates;
    std::map<int, std::shared_ptr<ButtonView>> buttons;
    std::map<int, std::shared_ptr<RockView>> rocks;
    std::map<int, std::shared_ptr<EnergyTransmitterView>> transmitters;
    std::map<int, std::shared_ptr<EnergyReceiverView>> receivers;
    std::map<int, std::shared_ptr<EnergyBallView>> balls;
    std::shared_ptr<CakeView> cake;
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
    void addButton(std::shared_ptr<ButtonView> button);
    void activateButton(int16_t id);
    void deactivateButton(int16_t id);
    void addChell(std::shared_ptr<ChellAnimationView> chell);
    void setChellState(int16_t id, ChellState state);
    void makeChellTiltedLeft(int16_t id);
    void makeChellTiltedRight(int16_t id);
    void makeChellNotTilted(int16_t id);
    void addRock(std::shared_ptr<RockView> rock);
    void removeRock(int16_t id);
    void setBackground(std::shared_ptr<BackgroundView> background);
    void addReceiver(std::shared_ptr<EnergyReceiverView> block);
    void activateReceiver(int16_t id);
    void addCake(std::shared_ptr<CakeView> cake);
    void addTransmitter(std::shared_ptr<EnergyTransmitterView> transmitter);
    void activateTransmitter(int16_t id);
    void addBall(std::shared_ptr<EnergyBallView> ball);
    void removeBall(int16_t id);

    void obtainXY(int &x, int &y, int x_m, int y_m);
};


#endif //SDL_WORLDVIEW_H
