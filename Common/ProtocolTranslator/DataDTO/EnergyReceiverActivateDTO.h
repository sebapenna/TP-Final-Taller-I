#ifndef PORTAL_ENERGYRECEIVERACTIVATEDTO_H
#define PORTAL_ENERGYRECEIVERACTIVATEDTO_H

#include "Common/ProtocolTranslator/ProtocolDTO.h"

class EnergyReceiverActivateDTO: public ProtocolDTO {
private:
    const int16_t _id;

public:
    explicit EnergyReceiverActivateDTO(const int16_t& id);

    ~EnergyReceiverActivateDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getId() const;
};


#endif //PORTAL_ENERGYRECEIVERACTIVATEDTO_H
