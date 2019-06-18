#include <Common/ProtocolTranslator/protocol_macros.h>
#include "ShootPortalDTO.h"

ShootPortalDTO::ShootPortalDTO(const int16_t &color, const int16_t &x,
                               const int16_t &y) :
_color(color), _x(x), _y(y) { }

ShootPortalDTO::~ShootPortalDTO() = default;

int16_t ShootPortalDTO::getClassId() const {
    return PROTOCOL_SHOOT_PORTAL;
}

const int16_t ShootPortalDTO::getColor() const {
    return _color;
}

const int16_t ShootPortalDTO::getX() const {
    return _x;
}

const int16_t ShootPortalDTO::getY() const {
    return _y;
}
