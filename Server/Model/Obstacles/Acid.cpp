#include "Acid.h"
#include <Server/Model/constants.h>

Acid::Acid(const float &x, const float &y, const float &width, const float &height) : _x(x), _y(y),
_width(width), _height(height) { }

const uint8_t Acid::classId() {
    return ACID;
}

void Acid::collideWith(Collidable *other) {
    // No realiza ninguna accion ante colision
}

void Acid::endCollitionWith(Collidable *other) {
    // No realiza ninguna accion ante fin colision
}

bool Acid::actedDuringStep() {
    return false;     // No realiza ninguna accion durante step
}

const float Acid::x() {
    return _x;
}

const float Acid::y() {
    return _y;
}

const float Acid::width() {
    return _width;
}

const float Acid::height() {
    return _height;
}
