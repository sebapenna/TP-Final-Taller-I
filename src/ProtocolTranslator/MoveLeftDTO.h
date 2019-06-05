#ifndef PORTAL_MOVELEFTDTO_H
#define PORTAL_MOVELEFTDTO_H

#include "ProtocolDTO.h"

class MoveLeftDTO: public ProtocolDTO {
public:
    int getClassId() const override;

    ~MoveLeftDTO() override;
};


#endif //PORTAL_MOVELEFTDTO_H
