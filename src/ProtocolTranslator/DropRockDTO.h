#ifndef PORTAL_DROPROCKDTO_H
#define PORTAL_DROPROCKDTO_H

#include "ProtocolDTO.h"

class DropRockDTO: public ProtocolDTO {
public:
    ~DropRockDTO() override;

    int getClassId() const override;
};


#endif //PORTAL_DROPROCKDTO_H
