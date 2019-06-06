#include "MoveRightDTO.h"
#include "constants.h"

MoveRightDTO::~MoveRightDTO() = default;

int MoveRightDTO::getClassId() const {
    return PROTOCOL_MOVE_RIGHT;
}
