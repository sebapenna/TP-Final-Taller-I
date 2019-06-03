#include "MetalDiagonalBlock.h"
#include <src/constants.h>

MetalDiagonalBlock::MetalDiagonalBlock(uint8_t o) :_orientation(o) { }

void MetalDiagonalBlock::collideWith(Collidable *other) {

}

const std::string MetalDiagonalBlock::getClassName() {
    return METAL_DIAGONAL_BLOCK;
}

void MetalDiagonalBlock::endCollitionWith(Collidable *other) {

}

