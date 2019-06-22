#include <cstdint>
#include "GateData.h"
#include <Server/Model/World.h>

GateData::GateData(const size_t &id, const float &x, const float &y) : _id
(id), _x(x), _y(y) { }

void GateData::addButtonNeeded(const size_t &id) {
    _buttons_needed.push_back(id);
}

void GateData::addEnergyReceiverNeeded(const size_t &id) {
    _energy_receivers_needed.push_back(id);
}

const size_t GateData::getId() const {
    return _id;
}

const float GateData::getX() const {
    return _x;
}

const float GateData::getY() const {
    return _y;
}

const std::vector<size_t> &GateData::getButtonsNeeded() const {
    return _buttons_needed;
}

const std::vector<size_t> &GateData::getEnergyReceiversNeeded() const {
    return _energy_receivers_needed;
}

void GateData::build(World *world, std::shared_ptr<Configuration> c) {
    auto body = BoxCreator::createStaticBox(world->getWorld(), _x, _y, c->getGateHalfWidth(),
            c->getGateHalfHeight());
    auto *gate = new Gate(world->getNextGateId(), _x, _y, c->getGateHalfWidth() * 2,
            c->getGateHalfHeight() * 2);

    for (auto &button_id : _buttons_needed)
        gate->addButtonNeeded(world->getButton(button_id));

    for (auto &e_rec_id : _energy_receivers_needed)
        gate->addEnergyReceiverNeeded(world->getEnergyReceiver(e_rec_id));

    body->SetUserData(gate);
    world->addGate(gate);
}

