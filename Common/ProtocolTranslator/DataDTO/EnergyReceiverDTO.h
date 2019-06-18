#ifndef PORTAL_ENERGYRECEIVERDTO_H
#define PORTAL_ENERGYRECEIVERDTO_H

#include "Common/ProtocolTranslator/ProtocolDTO.h"

class EnergyReceiverDTO: public ProtocolDTO {
private:
    const int16_t _id;
    const int16_t _x;
    const int16_t _y;
    const int16_t _side_length;
public:
    EnergyReceiverDTO(const int16_t& id, const int16_t& x, const int16_t& y,
                         const int16_t& side_length);

    ~EnergyReceiverDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getId() const;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getSideLength() const;

};


#endif //PORTAL_ENERGYRECEIVERDTO_H
