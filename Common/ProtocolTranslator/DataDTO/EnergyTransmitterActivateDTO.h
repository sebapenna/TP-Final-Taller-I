#ifndef PORTAL_ENERGYTRANSMITTERACTIVATEDTO_H
#define PORTAL_ENERGYTRANSMITTERACTIVATEDTO_H

#include <Common/ProtocolTranslator/ProtocolDTO.h>

class EnergyTransmitterActivateDTO: public ProtocolDTO {
private:
    const int16_t _id;

public:
    explicit EnergyTransmitterActivateDTO(const int16_t& id);

    ~EnergyTransmitterActivateDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getId() const;
};


#endif //PORTAL_ENERGYTRANSMITTERACTIVATEDTO_H
