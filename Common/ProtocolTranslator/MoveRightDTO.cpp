#include <Common/ProtocolTranslator/protocol_macros.h>
#include "MoveRightDTO.h"

MoveRightDTO::~MoveRightDTO() = default;

int16_t MoveRightDTO::getClassId() const {
    return PROTOCOL_MOVE_RIGHT;
}
