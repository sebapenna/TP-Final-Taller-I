#include "EnergyBarrierData.h"
#include <Server/constants.h>

EnergyBarrierData::EnergyBarrierData(const float &x, const float &y,
                                     const std::string &o) : _x(x), _y(y) {
    if (o == "V")
        _orientation = O_V;
    else
        _orientation = O_H;
}

const float EnergyBarrierData::getX() const {
    return _x;
}

const float EnergyBarrierData::getY() const {
    return _y;
}

const uint8_t EnergyBarrierData::getOrientation() const {
    return _orientation;
}
