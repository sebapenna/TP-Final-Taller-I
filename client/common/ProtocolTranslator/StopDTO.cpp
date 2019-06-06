#include "StopDTO.h"
#include "constants.h"

int StopDTO::getClassId() const {
    return PROTOCOL_STOP;
}

StopDTO::~StopDTO() = default;
