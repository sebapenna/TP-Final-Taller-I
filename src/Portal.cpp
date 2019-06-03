#include "Portal.h"
#include <src/constants.h>

Portal::Portal(uint8_t orientation) {
    _orientation = orientation;
}

void Portal::collideWith(Collidable *other) {

}

const std::string Portal::getClassName() {
    return PORTAL;
}
