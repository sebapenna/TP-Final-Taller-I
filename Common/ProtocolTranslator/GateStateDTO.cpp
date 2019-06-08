#include <Common/ProtocolTranslator/protocol_macros.h>
#include "GateStateDTO.h"

GateStateDTO::GateStateDTO(const int16_t &id, const int16_t &state) : _id(id), _state(state) { }

int16_t GateStateDTO::getClassId() const {
    return PROTOCOL_GATE_CHANGE_STATE;
}

const int16_t GateStateDTO::getId() const {
    return _id;
}

const int16_t GateStateDTO::getState() const {
    return _state;
}
