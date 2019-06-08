#include "EnergyReceiver.h"
#include <Server/EnergyBall.h>
#include <Server/Portal.h>
#include <Server/PinTool.h>

void EnergyReceiver::activate() {
    _state = ACTIVATED;
}

bool EnergyReceiver::isActivated() {
    return _activated;
}

void EnergyReceiver::updateState() {
    if (_state == ACTIVATED)
        _activated = true;
}

const std::string EnergyReceiver::getClassName() {
    return ENERGY_RECEIVER;
}

void EnergyReceiver::collideWith(Collidable *other) {
    if (other->getClassName() == ENERGY_BALL)
        this->activate();   // Se activa receptor
}

void EnergyReceiver::endCollitionWith(Collidable *other) {

}
