#ifndef PORTAL_QUITDTO_H
#define PORTAL_QUITDTO_H

#include "Common/ProtocolTranslator/ProtocolDTO.h"

class QuitDTO: public ProtocolDTO {
public:
    int16_t getClassId() const override;
};


#endif //PORTAL_QUITDTO_H
