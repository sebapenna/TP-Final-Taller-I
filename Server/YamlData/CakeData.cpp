#include "CakeData.h"

CakeData::CakeData(const float &x, const float &y) : _x(x), _y(y) { }

const float CakeData::getX() const {
    return _x;
}

const float CakeData::getY() const {
    return _y;
}
