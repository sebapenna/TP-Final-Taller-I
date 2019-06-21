#include "MetalDiagonalBlock.h"
#include <Server/Model/constants.h>

MetalDiagonalBlock::MetalDiagonalBlock(const float& x, const float& y, const float& width,
        const float& height, uint8_t o) : _x(x), _y(y), _width(width), _height(height),
        _orientation(o) { }

const uint8_t MetalDiagonalBlock::getOrientation() const {
    return _orientation;
}

const uint8_t MetalDiagonalBlock::classId() {
    return METAL_DIAGONAL_BLOCK;
}

void MetalDiagonalBlock::collideWith(Collidable *other) {
    // No realiza ninguna accion
}

void MetalDiagonalBlock::endCollitionWith(Collidable *other) {
    // No realiza ninguna accion
}

bool MetalDiagonalBlock::actedDuringStep() {
    return false;   // Nunca realiza accion durante un step
}

const float MetalDiagonalBlock::x() {
    return _x;
}

const float MetalDiagonalBlock::y() {
    return _y;
}

const float MetalDiagonalBlock::width() {
    return _width;
}

const float MetalDiagonalBlock::height() {
    return _height;
}

const float MetalDiagonalBlock::getCenterX() {
    return _x + _width / 2;
}

const float MetalDiagonalBlock::getCenterY() {
    return _y + _height / 2;
}

MetalDiagonalBlock::~MetalDiagonalBlock() = default;
