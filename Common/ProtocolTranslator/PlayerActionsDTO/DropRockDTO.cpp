#include "DropRockDTO.h"
#include <Common/ProtocolTranslator/protocol_macros.h>

DropRockDTO::~DropRockDTO() = default;

int16_t DropRockDTO::getClassId() const {
    return PROTOCOL_DROP_ROCK;
}
