#include <Common/ProtocolTranslator/protocol_macros.h>
#include "LiftRockDTO.h"

LiftRockDTO::LiftRockDTO(const int16_t &rock_id) : _rock_id(rock_id) { }

LiftRockDTO::~LiftRockDTO() = default;

int16_t LiftRockDTO::getClassId() const {
    return PROTOCOL_LIFT_ROCK;
}

const int16_t LiftRockDTO::getRockId() const {
    return _rock_id;
}
