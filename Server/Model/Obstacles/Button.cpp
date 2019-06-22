#include <Server/Model/Collidable.h>
#include <iostream>
#include <Box2D/Dynamics/b2Body.h>
#include "Button.h"

Button::Button(const size_t &id, const float& x, const float& y, const float& width,
               const float& height) : _id(id), _x(x), _y(y), _width(width), _height(height) { }

void Button::activate() {
    ++_bodies_on_it;
}

void Button::deactivate() {
    --_bodies_on_it;
}

bool Button::isActivated() {
    return _activated;
}

size_t Button::id() const {
    return _id;
}

const uint8_t Button::classId() {
    return BUTTON;
}

void Button::collideWith(Collidable *other) {
    auto c_name = other->classId();
    if (c_name == ROCK || c_name == CHELL)
        activate();
}

void Button::endCollitionWith(Collidable *other) {
    auto c_name = other->classId();
    if (c_name == ROCK || c_name == CHELL)
        deactivate();
}

bool Button::actedDuringStep() {
    if (_previous_state != _state) {
        _previous_state = _state;   // Actualizo previous step para evitar detectar falso cambio
        return true;
    }
    return false;
}

const float Button::x() {
    return _x;
}

const float Button::y() {
    return _y;
}

const float Button::width() {
    return _width;
}

const float Button::height() {
    return _height;
}

void Button::step(const float &time_step) {
    _activated = _bodies_on_it > 0;
    if (_activated)
        _state = ACTIVATED;
    else
        _state = NOT_ACTIVATED;
}

bool Button::isDead(const float &time_step) {
    return false;   // No se destruye
}

b2Body *Button::getBody() const {
    return nullptr; // No tiene body
}

Button::~Button() = default;
