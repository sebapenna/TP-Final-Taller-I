#include "JumpDTO.h"
#include <src/constants.h>

JumpDTO::~JumpDTO() = default;

int JumpDTO::getClassId() const {
    return PROTOCOL_JUMP;
}
