#ifndef PORTAL_STOPDTO_H
#define PORTAL_STOPDTO_H

#include "Common/ProtocolTranslator/ProtocolDTO.h"

class StopDTO: public ProtocolDTO {
public:
    ~StopDTO() override;

    int16_t getClassId() const override;
};


#endif //PORTAL_STOPDTO_H
