#ifndef PORTAL_LIFTROCKDTO_H
#define PORTAL_LIFTROCKDTO_H

#include "ProtocolDTO.h"

class LiftRockDTO: public ProtocolDTO {
private:
    const int16_t _rock_id;

public:
    explicit LiftRockDTO(const int16_t &rock_id);

    ~LiftRockDTO() override;

    int16_t getClassId() const override;

    const int16_t getRockId() const;
};

#endif //PORTAL_LIFTROCKDTO_H
