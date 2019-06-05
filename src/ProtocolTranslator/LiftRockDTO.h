#ifndef PORTAL_LIFTROCKDTO_H
#define PORTAL_LIFTROCKDTO_H

#include "ProtocolDTO.h"

class LiftRockDTO: public ProtocolDTO {
private:
    const int _rock_id;

public:
    explicit LiftRockDTO(const int& rock_id);

    ~LiftRockDTO() override;

    int getClassId() const override;

    const int getRockId() const;
};


#endif //PORTAL_LIFTROCKDTO_H
