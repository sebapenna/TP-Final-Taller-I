#include "RockBlock.h"
#include <src/constants.h>

const std::string RockBlock::getClassName() {
    return ROCK_BLOCK;
}

void RockBlock::collideWith(Collidable *other) {
    // No realiza ninguna accion
}

void RockBlock::endCollitionWith(Collidable *other) {
    // No realiza ninguna accion
}
