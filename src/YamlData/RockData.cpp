#include "RockData.h"

RockData::RockData(const size_t &id, const float &x, const float &y) :
_id(id), _x(x), _y(y) { }

size_t RockData::getId() const {
    return _id;
}

float RockData::getX() const {
    return _x;
}

float RockData::getY() const {
    return _y;
}
