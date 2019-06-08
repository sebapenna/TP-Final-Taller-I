#include <Common/ProtocolTranslator/protocol_macros.h>
#include "JumpDTO.h"

JumpDTO::~JumpDTO() = default;

int16_t JumpDTO::getClassId() const {
    return PROTOCOL_JUMP;
}
