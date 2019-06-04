#include <algorithm>

#include "MetalBlock.h"
#include <src/constants.h>

const std::string MetalBlock::getClassName() {
    return METAL_BLOCK;
}

void MetalBlock::collideWith(Collidable *other) {
    // No realiza ninguna accion
}

void MetalBlock::endCollitionWith(Collidable *other) {
    // No realiza ninguna accion

}
