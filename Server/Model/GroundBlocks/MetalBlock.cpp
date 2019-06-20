#include <algorithm>

#include "MetalBlock.h"
#include <Server/Model/constants.h>

const uint8_t MetalBlock::classId() {
    return METAL_BLOCK;
}

void MetalBlock::collideWith(Collidable *other) {
    // No realiza ninguna accion
}

void MetalBlock::endCollitionWith(Collidable *other) {
    // No realiza ninguna accion
}

bool MetalBlock::actedDuringStep() {
    return false;   // Nunca realiza accion durante un step
}

MetalBlock::MetalBlock(const float &x, const float &y, const float &width, const float &height) :
_x(x), _y(y), _width(width), _height(height) { }

const float MetalBlock::x() {
    return _x;
}

const float MetalBlock::y() {
    return _y;
}

const float MetalBlock::width() {
    return _width;
}

const float MetalBlock::height() {
    return _height;
}

MetalBlock::~MetalBlock() = default;
