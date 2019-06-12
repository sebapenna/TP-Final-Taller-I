#include "EnergyBarrier.h"
#include <Server/Model/constants.h>

EnergyBarrier::EnergyBarrier(const float &x, const float &y, const float &width,
                             const float &height) : _x(x), _y(y), _width(width), _height(height) { }

const uint8_t EnergyBarrier::getClassId() {
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

const float EnergyBarrier::getX() const {
    return _x;
}

const float EnergyBarrier::getY() const {
    return _y;
}

const float EnergyBarrier::getWidth() const {
    return _width;
}

const float EnergyBarrier::getHeight() const {
    return _height;
}