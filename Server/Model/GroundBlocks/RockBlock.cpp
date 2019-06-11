#include "RockBlock.h"
#include <Server/Model/constants.h>

RockBlock::RockBlock(const float &x, const float &y, const float &width, const float &height) :
_x(x), _y(y), _width(width), _height(height) { }

const uint8_t RockBlock::getClassId() {
    return ROCK_BLOCK;
}

void RockBlock::collideWith(Collidable *other) {
    // No realiza ninguna accion
}

void RockBlock::endCollitionWith(Collidable *other) {
    // No realiza ninguna accion
}

bool RockBlock::actedDuringStep() {
    return false;   // Nunca realiza accion durante un step
}

const float RockBlock::getX() const {
    return _x;
}

const float RockBlock::getY() const {
    return _y;
}

const float RockBlock::getWidth() const {
    return _width;
}

const float RockBlock::getHeight() const {
    return _height;
}
