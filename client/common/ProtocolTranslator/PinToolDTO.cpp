#include "PinToolDTO.h"
#include "constants.h"

PinToolDTO::PinToolDTO(const int &x, const int &y) : _x(x), _y(y) { }

PinToolDTO::~PinToolDTO() = default;

int PinToolDTO::getClassId() const {
    return PROTOCOL_PIN_TOOL;
}

const int PinToolDTO::getX() const {
    return _x;
}

const int PinToolDTO::getY() const {
    return _y;
}
