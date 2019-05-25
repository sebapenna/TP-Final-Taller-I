#include "energy_receiver.h"
#include "src/exceptions.h"

void EnergyReceiver::createPortal(uint8_t orientacion_rayo) {
    throw BlockCantCreatePortalException();
}

void EnergyReceiver::receiveEnergyBall() {
    _activated = true;
}

bool EnergyReceiver::isActivated() {
    return _activated;
}
