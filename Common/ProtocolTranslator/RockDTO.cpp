#include "RockDTO.h"

RockDTO::RockDTO(const int16_t &id, const int16_t &x, const int16_t &y, const int16_t &side_length,
                 const int16_t &delete_state) : _id(id), _x(x), _y(y), _side_length(side_length),
                 _delete_state(delete_state) { }

int16_t RockDTO::getClassId() const {
    return PROTOCOL_ROCK_DATA;
}

const int16_t RockDTO::getId() const {
    return _id;
}

const int16_t RockDTO::getX() const {
    return _x;
}

const int16_t RockDTO::getY() const {
    return _y;
}

const int16_t RockDTO::getSideLength() const {
    return _side_length;
}

const int16_t RockDTO::getDeleteState() const {
    return _delete_state;
}
