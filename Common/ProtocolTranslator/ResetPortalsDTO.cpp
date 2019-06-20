#include "ResetPortalsDTO.h"

ResetPortalsDTO::~ResetPortalsDTO() = default;

int16_t ResetPortalsDTO::getClassId() const {
    return PROTOCOL_RESET_PORTALS;
}
