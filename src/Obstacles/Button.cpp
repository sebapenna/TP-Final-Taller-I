#include <src/Collidable.h>
#include "Button.h"

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

void Button::collideWith(Collidable *other) {

}

const std::string Button::getClassName() {
    return BUTTON;
}

void Button::endCollitionWith(Collidable *other) {

}
