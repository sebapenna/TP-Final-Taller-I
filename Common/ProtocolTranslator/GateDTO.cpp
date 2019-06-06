#include "GateDTO.h"

GateDTO::GateDTO(const int16_t& id, const int16_t &x, const int16_t &y, const int16_t &width,
                 const int16_t &height) : _id(id), _x(x), _y(y), _width(width), _height(height) { }

int16_t GateDTO::getClassId() const {
    return PROTOCOL_GATE_DATA;
}

const int16_t GateDTO::getId() const {
    return _id;
}

const int16_t GateDTO::getX() const {
    return _x;
}

const int16_t GateDTO::getY() const {
    return _y;
}

const int16_t GateDTO::getWidth() const {
    return _width;
}

const int16_t GateDTO::getHeight() const {
    return _height;
}
