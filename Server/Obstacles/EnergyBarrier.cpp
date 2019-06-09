#include "EnergyBarrier.h"
#include <Server/constants.h>

const std::string EnergyBarrier::getClassName() {
    return ENERGY_BARRIER;
}

void EnergyBarrier::collideWith(Collidable *other) {
    // No realiza ninguna accion ante colision
}

void EnergyBarrier::endCollitionWith(Collidable *other) {
    // No realiza ninguna accion ante fin colision

}

bool EnergyBarrier::actedDuringStep() {
    return false;     // No realiza ninguna accion durante step
}
