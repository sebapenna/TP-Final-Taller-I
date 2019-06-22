#include <Server/Model/World.h>
#include "EnergyReceiverData.h"

EnergyReceiverData::EnergyReceiverData(const size_t &id, const float &x,
                                       const float &y) : _id(id), _x(x), _y(y){}

const size_t EnergyReceiverData::getId() const {
    return _id;
}

const float EnergyReceiverData::getX() const {
    return _x;
}

const float EnergyReceiverData::getY() const {
    return _y;
}

void
EnergyReceiverData::build(World *world, std::shared_ptr<Configuration> c) {
    auto body = BoxCreator::createStaticBox(world->getWorld(), _x, _y, c->getEnergyBlockHalfLen(),
            c->getEnergyBlockHalfLen());
    auto e_recv = new EnergyReceiver(world->getNextReceiverId(), _x, _y,
            c->getEnergyBlockHalfLen() * 2, c->getEnergyBlockHalfLen() * 2);
    body->SetUserData(e_recv);
    world->addEnergyReceiver(e_recv);
}

