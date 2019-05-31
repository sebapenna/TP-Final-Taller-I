#include "EnergyTransmitter.h"
#include "src/exceptions.h"
#include "../constants.h"
#include "../World.h"

EnergyTransmitter::EnergyTransmitter(b2Body *body, uint8_t direction) :
_body(body), _direction(direction) { }

void EnergyTransmitter::createPortal(uint8_t ray_orientaiton) {
    throw BlockCantCreatePortalException();
}

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
