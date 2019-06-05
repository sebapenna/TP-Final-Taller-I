#ifndef PORTAL_MOVERIGHTDTO_H
#define PORTAL_MOVERIGHTDTO_H

#include "ProtocolDTO.h"

class MoveRightDTO: public ProtocolDTO {
public:
    int getClassId() const override;

    ~MoveRightDTO() override;
};


#endif //PORTAL_MOVERIGHTDTO_H
