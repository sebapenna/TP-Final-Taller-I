#include "DropRockDTO.h"
#include <src/protocol_macros.h>

DropRockDTO::~DropRockDTO() = default;

int DropRockDTO::getClassId() const {
    return PROTOCOL_DROP_ROCK;
}
