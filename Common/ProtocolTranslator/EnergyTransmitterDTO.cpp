#include <Common/ProtocolTranslator/protocol_macros.h>
#include "EnergyTransmitterDTO.h"

EnergyTransmitterDTO::EnergyTransmitterDTO(const int16_t &id,  const int16_t &x, const int16_t &y,
        const int16_t &side_length, const int16_t &direction) :
        _id(id), _x(x), _y(y), _side_length(side_length), _direction(direction) { }

int16_t EnergyTransmitterDTO::getClassId() const {
    return PROTOCOL_ENERGY_TRANSMITTER_DATA;
}

const int16_t EnergyTransmitterDTO::getX() const {
    return _x;
}

const int16_t EnergyTransmitterDTO::getY() const {
    return _y;
}

const int16_t EnergyTransmitterDTO::getSideLength() const {
    return _side_length;
}

const int16_t EnergyTransmitterDTO::getDirection() const {
    return _direction;
}

const int16_t EnergyTransmitterDTO::getId() const {
    return _id;
}
