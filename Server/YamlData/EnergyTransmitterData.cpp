#include <string>
#include "EnergyTransmitterData.h"
#include "../constants.h"

EnergyTransmitterData::EnergyTransmitterData(const float &x, const float &y,
                                             const std::string &direction)
: _x(x), _y(y) {
    if (direction == "N")
        _direction = O_N;
    else if (direction == "S")
        _direction = O_S;
    else if (direction == "E")
        _direction = O_E;
    else
        _direction = O_O;
}

const float EnergyTransmitterData::getX() const {
    return _x;
}

const float EnergyTransmitterData::getY() const {
    return _y;
}

const uint8_t EnergyTransmitterData::getDirection() const {
    return _direction;
}
