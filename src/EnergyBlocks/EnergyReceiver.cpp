#include "EnergyReceiver.h"
#include "src/exceptions.h"

void EnergyReceiver::createPortal(uint8_t orientacion_rayo) {
    throw BlockCantCreatePortalException();
}

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
