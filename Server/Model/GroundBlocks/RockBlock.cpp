#include "RockBlock.h"
#include <Server/Model/constants.h>
#include <Box2D/Dynamics/b2Body.h>

RockBlock::RockBlock(const float &x, const float &y, const float &width, const float &height) :
_x(x), _y(y), _width(width), _height(height) { }

const uint8_t RockBlock::classId() {
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

const float RockBlock::x() {
    return _x;
}

const float RockBlock::y() {
    return _y;
}

const float RockBlock::width() {
    return _width;
}

const float RockBlock::height() {
    return _height;
}

void RockBlock::step(const float &time_step) {
    // No realiza accion en step
}

bool RockBlock::isDead(const float &time_step) {
    return false;   // No se destruye
}

b2Body *RockBlock::getBody() const {
    return nullptr; // No tiene body
}

RockBlock::~RockBlock() = default;
