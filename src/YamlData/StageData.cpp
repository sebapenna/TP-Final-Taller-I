#include <cstddef>
#include "StageData.h"

StageData::StageData(const size_t &height, const size_t &width) :
    _height(height), _width(width) { };

size_t StageData::getHeight() const {
    return _height;
}

size_t StageData::getWidth() const {
    return _width;
}
