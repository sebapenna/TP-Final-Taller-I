#include "CommitSuicideDTO.h"

CommitSuicideDTO::~CommitSuicideDTO() = default;

int16_t CommitSuicideDTO::getClassId() const {
    return PROTOCOL_COMMIT_SUICIDE;
}
