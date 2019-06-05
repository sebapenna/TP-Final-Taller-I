#include "MoveLeftDTO.h"
#include <src/constants.h>

MoveLeftDTO::~MoveLeftDTO() = default;

int MoveLeftDTO::getClassId() const {
    return PROTOCOL_MOVE_LEFT;
}
