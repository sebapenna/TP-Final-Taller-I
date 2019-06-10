#include "EnergyReceiver.h"
#include <Server/Model/EnergyBall.h>
#include <Server/Model/Portal.h>
#include <Server/Model/PinTool.h>

EnergyReceiver::EnergyReceiver(const size_t &id) : _id(id) { }

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
    // No tiene acciones al finalizar colisiones
}

bool EnergyReceiver::actedDuringStep() {
    if (_previous_state != _state) {
        _previous_state = _state;   // Actualizo previous state para evitar detectar falso cambio
        return true;
    }
    return false;
}

const size_t EnergyReceiver::getId() const {
    return _id;
}
