#ifndef PORTAL_ENERGYBALLDTO_H
#define PORTAL_ENERGYBALLDTO_H

#include "Common/ProtocolTranslator/ProtocolDTO.h"

class EnergyBallDTO: public ProtocolDTO {
private:
    const int16_t _id;
    const int16_t _x;
    const int16_t _y;
    const int16_t _radius;
    const int16_t _delete_state;
public:
    EnergyBallDTO(const int16_t& id, const int16_t& x, const int16_t& y, const int16_t& radius,
                  const int16_t& delete_state);

    ~EnergyBallDTO() override = default;

    int16_t getClassId() const override;

    const int16_t getId() const;

    const int16_t getX() const;

    const int16_t getY() const;

    const int16_t getRadius() const;

    const int16_t getDeleteState() const;
};


#endif //PORTAL_ENERGYBALLDTO_H
