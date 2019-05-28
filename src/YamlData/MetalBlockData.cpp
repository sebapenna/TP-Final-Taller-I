#include "MetalBlockData.h"

MetalBlockData::MetalBlockData(const float &width, const float &height,
                               const float &x, const float &y) :
                               _width(width), _height(height), _x(x), _y(y) { }

float MetalBlockData::getWidth() const {
    return _width;
}

float MetalBlockData::getHeight() const {
    return _height;
}

float MetalBlockData::getX() const {
    return _x;
}

float MetalBlockData::getY() const {
    return _y;
}
