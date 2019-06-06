#ifndef PORTAL_PROTOCOLDTO_H
#define PORTAL_PROTOCOLDTO_H

#include <cstdint>
#include <Common/ProtocolTranslator/protocol_macros.h>

class ProtocolDTO {
public:
    virtual ~ProtocolDTO() = default;
    virtual int16_t getClassId() const = 0;
};

#endif //PORTAL_PROTOCOLDTO_H
