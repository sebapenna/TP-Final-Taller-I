#include <string>
#include "EnergyTransmitterData.h"
#include "Server/Model/constants.h"
#include <Server/Model/World.h>

EnergyTransmitterData::EnergyTransmitterData(const float &x, const float &y,
                                             const std::string &direction)
: _x(x), _y(y) {
    if (direction == "N")
        _direction = O_N;
    else if (direction == "S")
        _direction = O_S;
    else if (direction == "E")
        _direction = O_E;
    else
        _direction = O_O;
}

const float EnergyTransmitterData::getX() const {
    return _x;
}

const float EnergyTransmitterData::getY() const {
    return _y;
}

const uint8_t EnergyTransmitterData::getDirection() const {
    return _direction;
}

void
EnergyTransmitterData::build(World *world, std::shared_ptr<Configuration> c) {
    auto body = BoxCreator::createStaticBox(world->getWorld(), _x, _y, c->getEnergyBlockHalfLen(),
            c->getEnergyBlockHalfLen());
    auto *e_transm = new EnergyTransmitter(world->getNextTransmitterId(), body, _direction,
            c->getEnergyBlockHalfLen() * 2, c->getEnergyBlockHalfLen() * 2,
            c->getTimeToReleaseEnrgBall());
    body->SetUserData(e_transm);
    world->addEnergyTransmitter(e_transm);
}
