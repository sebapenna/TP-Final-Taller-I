#include "EnergyTransmitter.h"
#include <Server/Model/constants.h>

EnergyTransmitter::EnergyTransmitter(const size_t &id, b2Body *body, uint8_t direction,
        const float& width, const float& height) : _body(body), _direction(direction), _id(id),
        _width(width), _height(height) { }

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

const uint8_t EnergyTransmitter::classId() {
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

size_t EnergyTransmitter::id() const {
    return _id;
}

const float EnergyTransmitter::x() {
    return _body->GetPosition().x;
}

const float EnergyTransmitter::y() {
    return _body->GetPosition().y;
}

const float EnergyTransmitter::width() {
    return _width;
}

const float EnergyTransmitter::height() {
    return _height;
}
