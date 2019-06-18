#include <Common/ProtocolTranslator/protocol_macros.h>
#include "PortalDTO.h"

PortalDTO::PortalDTO(const int16_t &id, const int16_t &x, const int16_t &y, const int16_t &width,
                     const int16_t &height, const int16_t &colour, const int16_t &delete_state) :
                     _id(id), _x(x), _y(y), _width(width), _height(height), _colour(colour),
                     _delete_state(delete_state) { }

int16_t PortalDTO::getClassId() const {
    return PROTOCOL_PORTAL_DATA;
}

const int16_t PortalDTO::getId() const {
    return _id;
}

const int16_t PortalDTO::getX() const {
    return _x;
}

const int16_t PortalDTO::getY() const {
    return _y;
}

const int16_t PortalDTO::getWidth() const {
    return _width;
}

const int16_t PortalDTO::getHeight() const {
    return _height;
}

const int16_t PortalDTO::getColour() const {
    return _colour;
}

const int16_t PortalDTO::getDeleteState() const {
    return _delete_state;
}
