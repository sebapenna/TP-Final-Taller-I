#include "LiftRockDTO.h"

LiftRockDTO::LiftRockDTO(const int &rock_id) : _rock_id(rock_id) { }

LiftRockDTO::~LiftRockDTO() = default;

int LiftRockDTO::getClassId() const {
    return PROTOCOL_LIFT_ROCK;
}

const int LiftRockDTO::getRockId() const {
    return _rock_id;
}
