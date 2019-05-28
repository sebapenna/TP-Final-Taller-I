#include "RockBlockData.h"

RockBlockData::RockBlockData(const float &width, const float &height,
                             const float &x, const float &y) :
                             _width(width), _height(height), _x(x), _y(y){ }

float RockBlockData::getWidth() const {
    return _width;
}

float RockBlockData::getHeight() const {
    return _height;
}

float RockBlockData::getX() const {
    return _x;
}

float RockBlockData::getY() const {
    return _y;
}
