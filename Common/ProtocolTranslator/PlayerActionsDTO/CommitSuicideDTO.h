#ifndef PORTAL_COMMITSUICIDEDTO_H
#define PORTAL_COMMITSUICIDEDTO_H

#include <Common/ProtocolTranslator/ProtocolDTO.h>

class CommitSuicideDTO: public ProtocolDTO {
public:
    ~CommitSuicideDTO() override;

    int16_t getClassId() const override;
};


#endif //PORTAL_COMMITSUICIDEDTO_H
