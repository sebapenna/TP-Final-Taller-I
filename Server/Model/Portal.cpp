#include "Portal.h"
#include <Server/Model/constants.h>

Portal::Portal(uint8_t orientation) {
    _orientation = orientation;
}

void Portal::collideWith(Collidable *other) {

}

const uint8_t Portal::getClassId() {
    return PORTAL_RAY;
}
