#include "PinToolDTO.h"

PinToolDTO::PinToolDTO(const int16_t &id, const int16_t &x, const int16_t &y, const int16_t &width,
                       const int16_t &height, const int16_t &delete_state) :
        _id(id), _x(x), _y(y), _width(width), _height(height), _delete_state(delete_state) { }

int16_t PinToolDTO::getClassId() const {
    return PROTOCOL_PIN_TOOL_DATA;
}

const int16_t PinToolDTO::getId() const {
    return _id;
}

const int16_t PinToolDTO::getX() const {
    return _x;
}

const int16_t PinToolDTO::getY() const {
    return _y;
}

const int16_t PinToolDTO::getWidth() const {
    return _width;
}

const int16_t PinToolDTO::getHeight() const {
    return _height;
}

const int16_t PinToolDTO::getDeleteState() const {
    return _delete_state;
}
