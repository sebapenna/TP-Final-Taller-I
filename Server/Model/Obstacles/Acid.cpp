#include "Acid.h"
#include <Server/Model/constants.h>

const std::string Acid::getClassName() {
    return ACID;
}

void Acid::collideWith(Collidable *other) {
    // No realiza ninguna accion ante colision
}

void Acid::endCollitionWith(Collidable *other) {
    // No realiza ninguna accion ante fin colision
}

bool Acid::actedDuringStep() {
    return false;     // No realiza ninguna accion durante step
}
