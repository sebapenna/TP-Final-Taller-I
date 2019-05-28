#include "ButtonData.h"

ButtonData::ButtonData(const size_t &id, const float &x, const float &y) :
_id(id), _x(x), _y(y) { }

size_t ButtonData::getId() const {
    return _id;
}

float ButtonData::getX() const {
    return _x;
}

float ButtonData::getY() const {
    return _y;
}
