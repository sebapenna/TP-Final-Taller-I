#include "AcidData.h"

AcidData::AcidData(const float &x, const float &y) : _x(x), _y(y) { }

const float AcidData::getX() const {
    return _x;
}

const float AcidData::getY() const {
    return _y;
}
