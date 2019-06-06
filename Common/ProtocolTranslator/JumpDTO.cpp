#include "JumpDTO.h"

JumpDTO::~JumpDTO() = default;

int16_t JumpDTO::getClassId() const {
    return PROTOCOL_JUMP;
}
