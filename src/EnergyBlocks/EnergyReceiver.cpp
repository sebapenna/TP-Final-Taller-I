#include "EnergyReceiver.h"
#include <src/EnergyBall.h>
#include <src/Portal.h>
#include <src/PinTool.h>

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
    if (other->getClassName() == ENERGY_BALL) {
        this->activate();   // Se activa receptor
        auto energy_ball  = (EnergyBall*) other;
        // Elimino EnergyBall
    } else if (other->getClassName() == PORTAL) {
        // Elimino Portal
    } else if (other->getClassName() == PIN_TOOL) {
        // Elimino PinTool
    }
    // Resto de colisiones no tienen efecto
}

void EnergyReceiver::endCollitionWith(Collidable *other) {

}
