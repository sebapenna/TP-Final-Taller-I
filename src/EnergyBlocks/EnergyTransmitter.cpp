#include "EnergyTransmitter.h"
#include "src/exceptions.h"
#include "../constants.h"

EnergyTransmitter::EnergyTransmitter(b2Body *body, uint8_t direction) :
_body(body), _direction(direction) { }

void EnergyTransmitter::createPortal(uint8_t ray_orientaiton) {
    throw BlockCantCreatePortalException();
}

void EnergyTransmitter::update(World &world) {
    _time_elapsed += TIME_STEP;
    if (_time_elapsed >= TIME_TO_RELEASE) {
        _time_elapsed = 0;
        world.createEnergyBall(_body, _direction);
    }
}
