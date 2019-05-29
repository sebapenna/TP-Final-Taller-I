#include "RockData.h"

RockData::RockData(const float &x, const float &y) : _x(x), _y(y) { }

float RockData::getX() const {
    return _x;
}

float RockData::getY() const {
    return _y;
}
