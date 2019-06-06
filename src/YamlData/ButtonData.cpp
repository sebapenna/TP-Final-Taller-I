#include "ButtonData.h"

ButtonData::ButtonData(const size_t &id, const float &x, const float &y) :
_id(id), _x(x), _y(y) { }

const size_t ButtonData::getId() const {
    return _id;
}

const float ButtonData::getX() const {
    return _x;
}

const float ButtonData::getY() const {
    return _y;
}
