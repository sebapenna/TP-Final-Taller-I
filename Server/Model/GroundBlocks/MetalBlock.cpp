#include <algorithm>

#include "MetalBlock.h"
#include <Server/Model/constants.h>

const uint8_t MetalBlock::getClassId() {
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

const float MetalBlock::getX() const {
    return _x;
}

const float MetalBlock::getY() const {
    return _y;
}

const float MetalBlock::getWidth() const {
    return _width;
}

const float MetalBlock::getHeight() const {
    return _height;
}
