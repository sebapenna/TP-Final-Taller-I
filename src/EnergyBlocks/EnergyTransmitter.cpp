#include "EnergyTransmitter.h"
#include <src/constants.h>

EnergyTransmitter::EnergyTransmitter(b2Body *body, uint8_t direction) :
_body(body), _direction(direction) { }

bool EnergyTransmitter::releaseEnergyBall() {
    _time_elapsed += TIME_STEP;
    if (_time_elapsed >= TIME_TO_RELEASE) {
        _time_elapsed = 0;
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

void EnergyTransmitter::collideWith(Collidable *other) {

}

const std::string EnergyTransmitter::getClassName() {
    return ENERGY_TRANSMITTER;
}

void EnergyTransmitter::endCollitionWith(Collidable *other) {

}
