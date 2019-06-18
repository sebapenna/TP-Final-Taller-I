#ifndef PORTAL_MOVERIGHTDTO_H
#define PORTAL_MOVERIGHTDTO_H

#include "Common/ProtocolTranslator/ProtocolDTO.h"

class MoveRightDTO: public ProtocolDTO {
public:
    int16_t getClassId() const override;

    ~MoveRightDTO() override;
};


#endif //PORTAL_MOVERIGHTDTO_H
