#include "MetalDiagonalBlockData.h"
#include "../../src/constants.h"

MetalDiagonalBlockData::MetalDiagonalBlockData(const float &width,
        const float &height, const float &x, const float &y,
        const std::string &orientation) : _width(width), _height(height),
        _x(x), _y(y) {
    if (orientation == "NE")
        _orientation = O_NE;
    else if (orientation == "NO")
        _orientation = O_NO;
    else if(orientation == "SO")
        _orientation = O_SO;
    else
        _orientation = O_SE;
}

float MetalDiagonalBlockData::getWidth() const {
    return _width;
}

float MetalDiagonalBlockData::getHeight() const {
    return _height;
}

float MetalDiagonalBlockData::getX() const {
    return _x;
}

float MetalDiagonalBlockData::getY() const {
    return _y;
}

uint8_t MetalDiagonalBlockData::getOrientation() const {
    return _orientation;
}
