#include <Common/ProtocolTranslator/protocol_macros.h>
#include "ShootPinToolDTO.h"

ShootPinToolDTO::ShootPinToolDTO(const int16_t &x, const int16_t &y) : _x(x), _y(y) { }

ShootPinToolDTO::~ShootPinToolDTO() = default;

int16_t ShootPinToolDTO::getClassId() const {
    return PROTOCOL_SHOOT_PIN_TOOL;
}

const int16_t ShootPinToolDTO::getX() const {
    return _x;
}

const int16_t ShootPinToolDTO::getY() const {
    return _y;
}

