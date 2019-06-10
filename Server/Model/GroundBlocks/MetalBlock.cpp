#include <algorithm>

#include "MetalBlock.h"
#include <Server/Model/constants.h>

const std::string MetalBlock::getClassName() {
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
