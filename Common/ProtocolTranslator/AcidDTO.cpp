#include "AcidDTO.h"

AcidDTO::AcidDTO(const int16_t &x, const int16_t &y, const int16_t &width, const int16_t &height) :
_x(x), _y(y), _width(width), _height(height) { }

int16_t AcidDTO::getClassId() const {
    return PROTOCOL_ACID_DATA;
}

const int16_t AcidDTO::getX() const {
    return _x;
}

const int16_t AcidDTO::getY() const {
    return _y;
}

const int16_t AcidDTO::getWidth() const {
    return _width;
}

const int16_t AcidDTO::getHeight() const {
    return _height;
}
