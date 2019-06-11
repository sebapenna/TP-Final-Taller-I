#ifndef PORTAL_BEGINDTO_H
#define PORTAL_BEGINDTO_H

#include "Common/ProtocolTranslator/ProtocolDTO.h"

class BeginDTO: public ProtocolDTO {
public:
    int16_t getClassId() const override;
};


#endif //PORTAL_BEGINDTO_H
