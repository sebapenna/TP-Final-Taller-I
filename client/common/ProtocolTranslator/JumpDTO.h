#ifndef PORTAL_JUMPDTO_H
#define PORTAL_JUMPDTO_H

#include "ProtocolDTO.h"

class JumpDTO: public ProtocolDTO {
public:
    int getClassId() const override;

    ~JumpDTO() override;
};


#endif //PORTAL_JUMPDTO_H
