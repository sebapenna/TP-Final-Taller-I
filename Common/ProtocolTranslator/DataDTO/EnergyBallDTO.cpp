#include <Common/ProtocolTranslator/protocol_macros.h>
#include "EnergyBallDTO.h"

EnergyBallDTO::EnergyBallDTO(const int16_t &id, const int16_t &x, const int16_t &y,
        const int16_t &radius, const int16_t &delete_state) : _id(id), _x(x), _y(y),
        _radius(radius), _delete_state(delete_state) { }

int16_t EnergyBallDTO::getClassId() const {
    return PROTOCOL_ENERGY_BALL_DATA;
}

const int16_t EnergyBallDTO::getId() const {
    return _id;
}

const int16_t EnergyBallDTO::getX() const {
    return _x;
}

const int16_t EnergyBallDTO::getY() const {
    return _y;
}

const int16_t EnergyBallDTO::getRadius() const {
    return _radius;
}

const int16_t EnergyBallDTO::getDeleteState() const {
    return _delete_state;
}
