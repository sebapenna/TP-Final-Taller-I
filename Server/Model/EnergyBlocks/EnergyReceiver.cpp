#include "EnergyReceiver.h"
#include <Server/Model/EnergyBall.h>
#include <Server/Model/Shots/Portal.h>
#include <Server/Model/Shots/PinTool.h>

EnergyReceiver::EnergyReceiver(const size_t &id, const float& x, const float& y, const float& width,
                               const float& height) : _id(id), _x(x), _y(y), _width(width),
                               _height(height) { }

void EnergyReceiver::activate() {
    _state = ACTIVATED;
}

bool EnergyReceiver::isActivated() {
    return _activated;
}

const uint8_t EnergyReceiver::classId() {
    return ENERGY_RECEIVER;
}

void EnergyReceiver::collideWith(Collidable *other) {
    if (other->classId() == ENERGY_BALL)
        this->activate();   // Se activa receptor
}

void EnergyReceiver::endCollitionWith(Collidable *other) {
    // No tiene acciones al finalizar colisiones
}

bool EnergyReceiver::actedDuringStep() {
    if (_previous_state != _state) {
        _previous_state = _state;   // Actualizo previous state para evitar detectar falso cambio
        return true;
    }
    return false;
}

const size_t EnergyReceiver::id() const {
    return _id;
}

const float EnergyReceiver::x() {
    return _x;
}

const float EnergyReceiver::y() {
    return _y;
}

const float EnergyReceiver::width() {
    return _width;
}

const float EnergyReceiver::height() {
    return _height;
}

void EnergyReceiver::step(const float &time_step) {
    if (_state == ACTIVATED)
        _activated = true;
}

bool EnergyReceiver::isDead(const float &time_step) {
    return false;   // No se destruye
}

b2Body *EnergyReceiver::getBody() const {
    return nullptr; // No tiene body
}

EnergyReceiver::~EnergyReceiver() = default;
