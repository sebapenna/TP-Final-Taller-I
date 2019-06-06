#include "MoveLeftDTO.h"

MoveLeftDTO::~MoveLeftDTO() = default;

int16_t MoveLeftDTO::getClassId() const {
    return PROTOCOL_MOVE_LEFT;
}
