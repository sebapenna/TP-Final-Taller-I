#include "StopDTO.h"

int16_t StopDTO::getClassId() const {
    return PROTOCOL_STOP;
}

StopDTO::~StopDTO() = default;
