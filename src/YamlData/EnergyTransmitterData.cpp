#include "EnergyTransmitterData.h"

EnergyTransmitterData::EnergyTransmitterData(const float &x, const float &y)
: _x(x), _y(y) { }

float EnergyTransmitterData::getX() const {
    return _x;
}

float EnergyTransmitterData::getY() const {
    return _y;
}
