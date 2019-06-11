#include <Server/Model/Collidable.h>
#include "Button.h"

Button::Button(const size_t &id, const float& x, const float& y) : _id(id), _x(x), _y(y) { }

void Button::activate() {
    _state = ACTIVATED;
}

void Button::deactivate() {
    _state = NOT_ACTIVATED;
}

bool Button::isActivated() {
    return _activated;
}

void Button::updateState() {
    switch (_state) {
        case ACTIVATED:
            _activated = true;
            break;
        case NOT_ACTIVATED:
            _activated = false;
            break;
    }
}

size_t Button::getId() const {
    return _id;
}

const uint8_t Button::getClassId() {
    return BUTTON;
}

void Button::collideWith(Collidable *other) {
    auto c_name = other->getClassId();
    if (c_name == ROCK || c_name == CHELL)
        this->activate();
}

void Button::endCollitionWith(Collidable *other) {
    auto c_name = other->getClassId();
    if (c_name == ROCK || c_name == CHELL)
        this->deactivate();
}

bool Button::actedDuringStep() {
    if (_previous_state != _state) {
        _previous_state = _state;   // Actualizo previous step para evitar detectar falso cambio
        return true;
    }
    return false;
}

const float Button::getX() const {
    return _x;
}

const float Button::getY() const {
    return _y;
}
