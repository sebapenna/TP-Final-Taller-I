#ifndef PORTAL_STOPDTO_H
#define PORTAL_STOPDTO_H

#include "ProtocolDTO.h"

class StopDTO: public ProtocolDTO {
public:
    ~StopDTO() override;

    int getClassId() const override;
};


#endif //PORTAL_STOPDTO_H