#include "DropRockDTO.h"
#include <src/protocol_macros.h>

DropRockDTO::~DropRockDTO() = default;

int16_t DropRockDTO::getClassId() const {
    return PROTOCOL_DROP_ROCK;
}
