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

    for (auto const& ball: balls) {
        if (camera->isInCamera(ball.second->getDst())) {
            ball.second->draw(*camera);
        }
    }

    for (auto const& transmitter: transmitters) {
        if (camera->isInCamera(transmitter.second->getDst())) {
            transmitter.second->draw(*camera);
        }
    }

    for (auto const& receiver: receivers) {
        if (camera->isInCamera(receiver.second->getDst())) {
            receiver.second->draw(*camera);
        }
    }

    for (auto const& button: buttons) {
        if (camera->isInCamera(button.second->getDst())) {
            button.second->draw(*camera);
        }
    }

    for (auto const& portal: portals) {
        if (camera->isInCamera(portal.second->getDst())) {
            portal.second->draw(*camera);
        }
    }

    for (auto const& pintool: pintools) {
        if (camera->isInCamera(pintool.second->getDst())) {
            pintool.second->draw(*camera);
        }
    }

    if (cake) {
        if (camera->isInCamera(cake->getDst())) {
            cake->draw(*camera);
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
        int pass_type = rocks[rock->getId()]->getTypeRock();
        rock->setTypeRock(pass_type);
    }
    rocks[rock->getId()] = rock;
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

void WorldView::addButton(std::shared_ptr<ButtonView> button) {
    buttons[button->getId()] = button;
}

void WorldView::activateButton(int16_t id) {
    buttons[id]->enable();
}

void WorldView::deactivateButton(int16_t id) {
    buttons[id]->disable();
}

void WorldView::addChell(std::shared_ptr<ChellAnimationView> chell) {
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

ChellState WorldView::getChellState(int16_t id) {
    return chells[id]->getState();
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

void WorldView::setBackground(std::shared_ptr<BackgroundView> background) {
    this->background = background;
}

void WorldView::addReceiver(std::shared_ptr<EnergyReceiverView> block) {
    receivers[block->getId()] = block;
}

void WorldView::activateReceiver(int16_t id) {
    receivers[id]->activate();
}

void WorldView::addCake(std::shared_ptr<CakeView> cake) {
    this->cake = cake;
}

void WorldView::addTransmitter(std::shared_ptr<EnergyTransmitterView> transmitter) {
    transmitters[transmitter->getId()] = transmitter;
}

void WorldView::activateTransmitter(int16_t id) {
    transmitters[id]->transmite();
}

void WorldView::addBall(std::shared_ptr<EnergyBallView> ball) {
    // TODO: si la bola ya existe, simplemente modificar la posicion..
    //// THIS GETS FIXED ONCE I TRANSFER ALL THE LOGIC OF PIXELS TO THE CAMERA
    //// AND OUTSIDE THE CAMERA ALL SHOULD BE IN METERS.
    balls[ball->getId()] = ball;
}

void WorldView::removeBall(int16_t id) {
    balls.erase(id);
}

void WorldView::removeRock(int16_t id) {
    rocks.erase(id);
}

void WorldView::obtainXY(int &x, int &y, int x_m, int y_m, Renderer& renderer) {
    camera->obtainXY(x, y, x_m, y_m, renderer);
}

void WorldView::addPortal(int16_t id, std::shared_ptr<View> portal) {
    portals[id] = portal;
}

void WorldView::removePortal(int16_t id) {
    portals.erase(id);
}

void WorldView::addPinTool(std::shared_ptr<PinToolView> pintool) {
    pintools[pintool->getId()] = pintool;
}

void WorldView::removePinTool(int16_t id) {
    pintools.erase(id);
}
