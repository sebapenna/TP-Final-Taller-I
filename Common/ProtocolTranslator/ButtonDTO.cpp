#include "ButtonDTO.h"

ButtonDTO::ButtonDTO(const int16_t& id, const int16_t &x, const int16_t &y, const int16_t &width,
        const int16_t &height) : _id(id), _x(x), _y(y), _width(width), _height(height) { }

int16_t ButtonDTO::getClassId() const {
    return PROTOCOL_BUTTON_DATA;
}

const int16_t ButtonDTO::getX() const {
    return _x;
}

const int16_t ButtonDTO::getY() const {
    return _y;
}

const int16_t ButtonDTO::getWidth() const {
    return _width;
}

const int16_t ButtonDTO::getHeight() const {
    return _height;
}

const int16_t ButtonDTO::getId() const {
    return _id;
}
