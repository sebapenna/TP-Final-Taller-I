#include "EnergyTransmitter.h"
#include <Server/constants.h>

EnergyTransmitter::EnergyTransmitter(b2Body *body, uint8_t direction) :
_body(body), _direction(direction) { }

bool EnergyTransmitter::releaseEnergyBall() {
    _time_elapsed += TIME_STEP;
    if (_time_elapsed >= TIME_TO_RELEASE) {
        _time_elapsed = 0;
        _changed_state = true;
        return true;
    }
    return false;
}

b2Body *EnergyTransmitter::getBody() const {
    return _body;
}

uint8_t EnergyTransmitter::getDirection() const {
    return _direction;
}

const std::string EnergyTransmitter::getClassName() {
    return ENERGY_TRANSMITTER;
}

void EnergyTransmitter::collideWith(Collidable *other) {
    // No realiza accion al detectar colision
}

void EnergyTransmitter::endCollitionWith(Collidable *other) {
    // No realiza accion al finalizar colision
}

bool EnergyTransmitter::actedDuringStep() {
    if (_changed_state) {
        _changed_state = false; // Reseteo booleano para no detectar falso cambio de estado
        return true;
    }
    return false;
}
