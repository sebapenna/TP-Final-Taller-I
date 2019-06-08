#include "RockData.h"

RockData::RockData(const float &x, const float &y) : _x(x), _y(y) { }

const float RockData::getX() const {
    return _x;
}

const float RockData::getY() const {
    return _y;
}
