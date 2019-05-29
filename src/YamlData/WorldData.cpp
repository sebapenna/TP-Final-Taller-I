#include <cstddef>
#include "WorldData.h"

WorldData::WorldData(const size_t &height, const size_t &width) :
    _height(height), _width(width) { };

size_t WorldData::getHeight() const {
    return _height;
}

size_t WorldData::getWidth() const {
    return _width;
}
