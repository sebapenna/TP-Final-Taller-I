#include "CakeDTO.h"

CakeDTO::CakeDTO(const int16_t &x, const int16_t &y, const int16_t &side_length) :_x(x), _y(y),
_side_length(side_length) { }

int16_t CakeDTO::getClassId() const {
    return PROTOCOL_CAKE_DATA;
}

const int16_t CakeDTO::getX() const {
    return _x;
}

const int16_t CakeDTO::getY() const {
    return _y;
}

const int16_t CakeDTO::getSideLength() const {
    return _side_length;
}
