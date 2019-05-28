#include "Button.h"

Button::Button(b2Body *body) {
    _body = body;
    _activated = false;
}

void Button::activate() {
    _activated = true;
}

void Button::deactivate() {
    _activated = false;
}

bool Button::isActivated() {
    return _activated;
}

Button &Button::operator=(Button &&other) {
    this->_activated = other._activated;
    return *this;
}
