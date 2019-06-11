#include "Acid.h"
#include <Server/Model/constants.h>

Acid::Acid(const float &x, const float &y) : _x(x), _y(y) { }

const uint8_t Acid::getClassId() {
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

const float Acid::getX() const {
    return _x;
}

const float Acid::getY() const {
    return _y;
}
