#include "PortalDTO.h"
#include "constants.h"

PortalDTO::PortalDTO(const int &color, const int &x, const int &y) :
_color(color), _x(x), _y(y) { }

PortalDTO::~PortalDTO() = default;

int PortalDTO::getClassId() const {
    return PROTOCOL_PORTAL;
}

int PortalDTO::getColor() const {
    return _color;
}

int PortalDTO::getX() const {
    return _x;
}

int PortalDTO::getY() const {
    return _y;
}

