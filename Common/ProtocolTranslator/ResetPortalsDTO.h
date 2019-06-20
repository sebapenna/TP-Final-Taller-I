#ifndef PORTAL_RESETPORTALSDTO_H
#define PORTAL_RESETPORTALSDTO_H


#include "ProtocolDTO.h"

class ResetPortalsDTO: public ProtocolDTO {
public:
    ~ResetPortalsDTO() override;

    int16_t getClassId() const override;
};


#endif //PORTAL_RESETPORTALSDTO_H
