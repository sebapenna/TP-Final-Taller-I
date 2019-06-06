#ifndef PORTAL_JUMPDTO_H
#define PORTAL_JUMPDTO_H

#include "ProtocolDTO.h"

class JumpDTO: public ProtocolDTO {
public:
    int16_t getClassId() const override;

    ~JumpDTO() override;
};


#endif //PORTAL_JUMPDTO_H
