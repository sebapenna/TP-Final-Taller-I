#include "EnergyReceiverData.h"

EnergyReceiverData::EnergyReceiverData(const size_t &id, const float &x,
                                       const float &y) : _id(id), _x(x), _y(y){}

size_t EnergyReceiverData::getId() const {
    return _id;
}

float EnergyReceiverData::getX() const {
    return _x;
}

float EnergyReceiverData::getY() const {
    return _y;
}
