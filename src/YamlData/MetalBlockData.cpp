#include "MetalBlockData.h"

MetalBlockData::MetalBlockData(const float &width, const float &height,
                               const float &x, const float &y) :
                               _width(width), _height(height), _x(x), _y(y) { }

const float MetalBlockData::getWidth() const {
    return _width;
}

const float MetalBlockData::getHeight() const {
    return _height;
}

const float MetalBlockData::getX() const {
    return _x;
}

const float MetalBlockData::getY() const {
    return _y;
}
