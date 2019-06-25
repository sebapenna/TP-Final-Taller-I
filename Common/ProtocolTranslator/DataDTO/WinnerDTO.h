#ifndef PORTAL_WINNERDTO_H
#define PORTAL_WINNERDTO_H

#include <Common/ProtocolTranslator/ProtocolDTO.h>

class WinnerDTO : public ProtocolDTO {
public:
    ~WinnerDTO() override;

    int16_t getClassId() const override;
};


#endif //PORTAL_WINNERDTO_H
