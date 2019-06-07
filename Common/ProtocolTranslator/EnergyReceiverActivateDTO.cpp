#include "EnergyReceiverActivateDTO.h"

EnergyReceiverActivateDTO::EnergyReceiverActivateDTO(const int16_t &id) : _id(id) { }

int16_t EnergyReceiverActivateDTO::getClassId() const {
    return PROTOCOL_ENERGY_RECEIVER_ACTIVATE;
}

const int16_t EnergyReceiverActivateDTO::getId() const {
    return _id;
}
