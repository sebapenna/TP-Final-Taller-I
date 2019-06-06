#include "PlayerChellIdDTO.h"

PlayerChellIdDTO::PlayerChellIdDTO(const int16_t &id) : _chell_id(id){ }

PlayerChellIdDTO::~PlayerChellIdDTO() = default;

int16_t PlayerChellIdDTO::getClassId() const {
    return PROTOCOL_PLAYER_CHELL_ID;
}

const int16_t PlayerChellIdDTO::getChellId() const {
    return _chell_id;
}
