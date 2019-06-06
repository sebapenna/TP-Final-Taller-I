#include "MetalBlockDTO.h"

MetalBlockDTO::MetalBlockDTO(const int16_t &x, const int16_t &y,
         const int16_t &width, const int16_t &height) :
_x(x), _y(y), _width(width), _height(height) { }

int16_t MetalBlockDTO::getClassId() const {
    return PROTOCOL_METAL_BLOCK_DATA;
}

const int16_t MetalBlockDTO::getX() const {
    return _x;
}

const int16_t MetalBlockDTO::getY() const {
    return _y;
}

const int16_t MetalBlockDTO::getWidth() const {
    return _width;
}

const int16_t MetalBlockDTO::getHeight() const {
    return _height;
}

