#include "ButtonStateDTO.h"

ButtonStateDTO::ButtonStateDTO(const int16_t &id, const int16_t &state) : _id(id), _state(state) { }

int16_t ButtonStateDTO::getClassId() const {
    return PROTOCOL_BUTTON_CHANGE_STATE;
}

const int16_t ButtonStateDTO::getId() const {
    return _id;
}

const int16_t ButtonStateDTO::getState() const {
    return _state;
}
