#include "EnergyBarrierDTO.h"

EnergyBarrierDTO::EnergyBarrierDTO(const int16_t &x, const int16_t &y,
        const int16_t &width, const int16_t &height) : _x(x), _y(y), _width(width),
        _height(height) { }

int16_t EnergyBarrierDTO::getClassId() const {
    return PROTOCOL_ENERGY_BARRIER_DATA;
}

const int16_t EnergyBarrierDTO::getX() const {
    return _x;
}

const int16_t EnergyBarrierDTO::getY() const {
    return _y;
}

const int16_t EnergyBarrierDTO::getWidth() const {
    return _width;
}

const int16_t EnergyBarrierDTO::getHeight() const {
    return _height;
}
