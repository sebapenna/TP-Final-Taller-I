#include "JumpDTO.h"
#include "constants.h"

JumpDTO::~JumpDTO() = default;

int JumpDTO::getClassId() const {
    return PROTOCOL_JUMP;
}
