#include "WinnerDTO.h"

WinnerDTO::~WinnerDTO() = default;

int16_t WinnerDTO::getClassId() const {
    return PROTOCOL_WINNER;
}
