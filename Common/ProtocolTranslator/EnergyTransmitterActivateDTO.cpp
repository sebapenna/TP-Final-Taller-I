#include "EnergyTransmitterActivateDTO.h"

EnergyTransmitterActivateDTO::EnergyTransmitterActivateDTO(const int16_t &id) : _id(id) { }

int16_t EnergyTransmitterActivateDTO::getClassId() const {
    return PROTOCOL_ENERGY_TRANSMITTER_ACTIVATE;
}

const int16_t EnergyTransmitterActivateDTO::getId() const {
    return _id;
}
