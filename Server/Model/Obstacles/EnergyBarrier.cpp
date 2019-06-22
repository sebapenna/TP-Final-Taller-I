#include "EnergyBarrier.h"
#include <Server/Model/constants.h>
#include <Box2D/Dynamics/b2Body.h>

EnergyBarrier::EnergyBarrier(const float &x, const float &y, const float &width,
                             const float &height) : _x(x), _y(y), _width(width), _height(height) { }

const uint8_t EnergyBarrier::classId() {
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

const float EnergyBarrier::x() {
    return _x;
}

const float EnergyBarrier::y() {
    return _y;
}

const float EnergyBarrier::width() {
    return _width;
}

const float EnergyBarrier::height() {
    return _height;
}

void EnergyBarrier::step(const float &time_step) {
    // No realiza accion en step
}

bool EnergyBarrier::isDead(const float &time_step) {
    return false;   // No se destruye
}

b2Body *EnergyBarrier::getBody() const {
    return nullptr; // No tiene body
}

EnergyBarrier::~EnergyBarrier() = default;
