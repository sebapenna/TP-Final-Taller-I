#ifndef PORTAL_KILLMISSINGCHELLDTO_H
#define PORTAL_KILLMISSINGCHELLDTO_H

#include <Common/ProtocolTranslator/ProtocolDTO.h>

class KillMissingChellDTO: public ProtocolDTO {
public:
    ~KillMissingChellDTO() override;

    int16_t getClassId() const override;
};


#endif //PORTAL_KILLMISSINGCHELLDTO_H
