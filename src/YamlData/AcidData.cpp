#include "AcidData.h"

AcidData::AcidData(const float &x, const float &y) : _x(x), _y(y) { }

float AcidData::getX() const {
    return _x;
}

float AcidData::getY() const {
    return _y;
}
