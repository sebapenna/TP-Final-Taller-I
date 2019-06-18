#ifndef PORTAL_MOVELEFTDTO_H
#define PORTAL_MOVELEFTDTO_H

#include "Common/ProtocolTranslator/ProtocolDTO.h"

class MoveLeftDTO: public ProtocolDTO {
public:
    int16_t getClassId() const override;

    ~MoveLeftDTO() override;
};


#endif //PORTAL_MOVELEFTDTO_H
