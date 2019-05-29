#include "ChellData.h"

ChellData::ChellData(const size_t &id, const float &x, const float &y) :
_id(id), _x(x), _y(y) { }

size_t ChellData::getId() const {
    return _id;
}

float ChellData::getX() const {
    return _x;
}

float ChellData::getY() const {
    return _y;
}
