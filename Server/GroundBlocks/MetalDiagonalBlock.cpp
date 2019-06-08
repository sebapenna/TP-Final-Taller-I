#include "MetalDiagonalBlock.h"
#include <Server/constants.h>

MetalDiagonalBlock::MetalDiagonalBlock(uint8_t o) :_orientation(o) { }

const uint8_t MetalDiagonalBlock::getOrientation() const {
    return _orientation;
}

const std::string MetalDiagonalBlock::getClassName() {
    return METAL_DIAGONAL_BLOCK;
}

void MetalDiagonalBlock::collideWith(Collidable *other) {
    // No realiza ninguna accion
}

void MetalDiagonalBlock::endCollitionWith(Collidable *other) {
    // No realiza ninguna accion
}

