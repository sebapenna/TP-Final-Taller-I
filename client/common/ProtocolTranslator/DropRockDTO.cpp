#include "DropRockDTO.h"
#include "constants.h"

DropRockDTO::~DropRockDTO() = default;

int DropRockDTO::getClassId() const {
    return PROTOCOL_DROP_ROCK;
}
