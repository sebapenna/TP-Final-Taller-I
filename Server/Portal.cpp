#include "Portal.h"
#include <Server/constants.h>

Portal::Portal(uint8_t orientation) {
    _orientation = orientation;
}

void Portal::collideWith(Collidable *other) {

}

const std::string Portal::getClassName() {
    return PORTAL_RAY;
}
