#include "ChellDTO.h"

ChellDTO::ChellDTO(const int16_t &id, const int16_t &x, const int16_t &y, const int16_t& width,
                   const int16_t& height, const int16_t &direction, const int16_t &tilted,
                   const int16_t& moving, const int16_t &jumping, const int16_t &shooting,
                   const int16_t &carrying_rock, const int16_t &delete_state) : _id(id), _x(x),
                   _y(y), _width(width), _height(height), _direction(direction), _tilted(tilted),
                   _jumping(jumping), _moving(moving), _shooting(shooting),
                   _carrying_rock(carrying_rock), _delete_state(delete_state) {
}

int16_t ChellDTO::getClassId() const {
    return PROTOCOL_CHELL_DATA;
}

const int16_t ChellDTO::getWidth() const {
    return _width;
}

const int16_t ChellDTO::getHeight() const {
    return _height;
}

const int16_t ChellDTO::getMoving() const {
    return _moving;
}

const int16_t ChellDTO::getId() const {
    return _id;
}

const int16_t ChellDTO::getX() const {
    return _x;
}

const int16_t ChellDTO::getY() const {
    return _y;
}

const int16_t ChellDTO::getDirection() const {
    return _direction;
}

const int16_t ChellDTO::getTilted() const {
    return _tilted;
}

const int16_t ChellDTO::getJumping() const {
    return _jumping;
}

const int16_t ChellDTO::getShooting() const {
    return _shooting;
}

const int16_t ChellDTO::getCarryingRock() const {
    return _carrying_rock;
}

const int16_t ChellDTO::getDeleteState() const {
    return _delete_state;
}
