#include "StopDTO.h"
#include <src/constants.h>

int StopDTO::getClassId() const {
    return PROTOCOL_STOP;
}

StopDTO::~StopDTO() = default;
