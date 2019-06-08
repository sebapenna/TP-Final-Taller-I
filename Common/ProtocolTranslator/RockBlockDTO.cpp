#include <Common/ProtocolTranslator/protocol_macros.h>
#include "RockBlockDTO.h"

RockBlockDTO::RockBlockDTO(const int16_t &x, const int16_t &y,
                           const int16_t &width, const int16_t &height) :
                           _x(x), _y(y), _width(width), _height(height) { }

int16_t RockBlockDTO::getClassId() const {
    return PROTOCOL_ROCK_BLOCK_DATA;
}

const int16_t RockBlockDTO::getX() const {
    return _x;
}

const int16_t RockBlockDTO::getY() const {
    return _y;
}

const int16_t RockBlockDTO::getWidth() const {
    return _width;
}

const int16_t RockBlockDTO::getHeight() const {
    return _height;
}
