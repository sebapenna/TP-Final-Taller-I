#ifndef PORTAL_ENERGYTRANSMITTERDTO_H
#define PORTAL_ENERGYTRANSMITTERDTO_H

#include "ProtocolDTO.h"

class EnergyTransmitterDTO: public ProtocolDTO {
private:
    const int16_t _id;
    const int16_t _x;
    const int16_t _y;
    const int16_t _side_length;
    const int16_t _direction;
public:
    EnergyTransmitterDTO(const int16_t& id, const int16_t& x, const int16_t& y,
                         const int16_t& side_length, const int16_t& direction);

    ~EnergyTransmitterDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getSideLength() const;

    const int16_t getDirection() const;

    const int16_t getId() const;
};


#endif //PORTAL_ENERGYTRANSMITTERDTO_H
