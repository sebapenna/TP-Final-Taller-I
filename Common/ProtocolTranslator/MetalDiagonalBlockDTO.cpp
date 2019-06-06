#include "MetalDiagonalBlockDTO.h"

MetalDiagonalBlockDTO::MetalDiagonalBlockDTO(const int16_t &x, const int16_t &y,
        const int16_t &side_length, const int16_t &orientation) :
        _x(x), _y(y), _side_length(side_length), _orientation(orientation) { }

int16_t MetalDiagonalBlockDTO::getClassId() const {
    return PROTOCOL_METAL_DIAGONAL_BLOCK_DATA;
}

const int16_t MetalDiagonalBlockDTO::getX() const {
    return _x;
}

const int16_t MetalDiagonalBlockDTO::getY() const {
    return _y;
}

const int16_t MetalDiagonalBlockDTO::getSideLength() const {
    return _side_length;
}

const int16_t MetalDiagonalBlockDTO::getOrientation() const {
    return _orientation;
}
