#include "ChellData.h"

ChellData::ChellData(const size_t &id, const float &x, const float &y) :
_id(id), _x(x), _y(y) { }

const size_t ChellData::getId() const {
    return _id;
}

const float ChellData::getX() const {
    return _x;
}

const float ChellData::getY() const {
    return _y;
}
