#include "Button.h"
#include "../constants.h"

Button::Button(const size_t id, b2Body *body) : _id(id) {
    _body = body;
    _state = NOT_PRESSED;
    _activated = false;
}

void Button::activate() {
    _state = PRESSED;
}

void Button::deactivate() {
    _state = NOT_PRESSED;
}

bool Button::isActivated() {
    return _activated;
}

const size_t Button::getId() const {
    return _id;
}

void Button::updateState() {
    switch (_state) {
        case PRESSED:
            _activated = true;
            break;
        case NOT_PRESSED:
            _activated = false;
            break;
    }
}
