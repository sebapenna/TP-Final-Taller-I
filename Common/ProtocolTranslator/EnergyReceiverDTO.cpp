#include "EnergyReceiverDTO.h"

EnergyReceiverDTO::EnergyReceiverDTO(const int16_t &id, const int16_t &x, const int16_t &y,
                                     const int16_t &side_length) : _id(id), _x(x), _y(y),
                                     _side_length(side_length) { }

int16_t EnergyReceiverDTO::getClassId() const {
    return PROTOCOL_ENERGY_RECEIVER_DATA;
}

const int16_t EnergyReceiverDTO::getId() const {
    return _id;
}

const int16_t EnergyReceiverDTO::getX() const {
    return _x;
}

const int16_t EnergyReceiverDTO::getY() const {
    return _y;
}

const int16_t EnergyReceiverDTO::getSideLength() const {
    return _side_length;
}
