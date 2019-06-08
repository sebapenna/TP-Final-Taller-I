#include "EnergyReceiverData.h"

EnergyReceiverData::EnergyReceiverData(const size_t &id, const float &x,
                                       const float &y) : _id(id), _x(x), _y(y){}

const size_t EnergyReceiverData::getId() const {
    return _id;
}

const float EnergyReceiverData::getX() const {
    return _x;
}

const float EnergyReceiverData::getY() const {
    return _y;
}
