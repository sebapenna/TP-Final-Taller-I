#include "MoveLeftDTO.h"
#include "constants.h"

MoveLeftDTO::~MoveLeftDTO() = default;

int MoveLeftDTO::getClassId() const {
    return PROTOCOL_MOVE_LEFT;
}
