//
// Created by jonathanmedina on 02/06/19.
//

#include "WorldView.h"

WorldView::WorldView() : camera(nullptr){}

WorldView::~WorldView() {
    if (camera) {
        delete camera;
    }
}


void WorldView::draw() {
    if (camera == nullptr) return;
    background->draw(*camera);
    for(auto const& view: views) {
        if (camera->isInCamera(view->getDst())) {
            view->draw(*camera);
        }
    }

    for(auto const& rock: rocks) {
        if (camera->isInCamera(rock.second->getDst())) {
            rock.second->draw(*camera);
        }
    }

    for(auto const& gate: gates) {
        if (camera->isInCamera(gate.second->getDst())) {
            gate.second->draw(*camera);
        }
    }

    for (auto const& button: buttons) {
        if (camera->isInCamera(button.second->getDst())) {
            button.second->draw(*camera);
        }
    }
    for(auto const& chell: chells) {
        if (camera->isInCamera(chell.second->getDst())) {
            chell.second->draw(*camera);
        }
        if (chell.second->isDead()) {
            chells.erase(chell.first);
        }
    }
}

void WorldView::addView(std::shared_ptr<View> view) {
    views.push_back(view);
}
void WorldView::addRock(std::shared_ptr<RockView> rock) {
    if (rocks.count(rock->getId())) {
        rocks[rock->getId()]->setDestRect(rock->getDst()->x, rock->getDst()->y, rock->getDst()->w, rock->getDst()->h);
    } else {
        rocks[rock->getId()] = rock;
    }
}
void WorldView::addGates(std::shared_ptr<GateView> gate) {
    gates[gate->getId()] = gate;
}

void WorldView::openGate(int16_t id) {
    auto gate = gates[id];
    gate->open();
}

void WorldView::closeGate(int16_t id) {
    auto gate = gates[id];
    gate->close();
}

void WorldView::addButton(std::shared_ptr<ButtonView>& button) {
    buttons[button->getId()] = button;
}

void WorldView::activateButton(int16_t id) {
    buttons[id]->enable();
}

void WorldView::deactivateButton(int16_t id) {
    buttons[id]->disable();
}

void WorldView::addChell(std::shared_ptr<ChellAnimationView>& chell) {
    if (chells.count(chell->getId())) {
        auto chellView = chells[chell->getId()];
        chellView->setPosition(chell->getPosition());
    } else {
        chells[chell->getId()] = chell;
    }
}

void WorldView::setChellState(int16_t id, ChellState state) {
    auto chell = chells[id];
    chell->setState(state);
}

void WorldView::makeChellTiltedLeft(int16_t id) {
    auto chell = chells[id];
    chell->setTiltedState(ChellIsTilted::TILTEDLEFT);
}

void WorldView::makeChellTiltedRight(int16_t id) {
    auto chell = chells[id];
    chell->setTiltedState(ChellIsTilted::TILTEDRIGHT);
}

void WorldView::makeChellNotTilted(int16_t id) {
    auto chell = chells[id];
    chell->setTiltedState(ChellIsTilted::NO);
}

void WorldView::setCamara(int16_t id, int w, int h) {
    auto chellView = chells[id];
    this->camera = new Camera(w, h, chellView->getPosition());
}

void WorldView::setBackground(std::shared_ptr<BackgroundView>& background) {
    this->background = background;
    //this->background->setDestRect(0,0,10,10);
    //this->background->setPosition(camera->getPosition());
}