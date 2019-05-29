#include "GateData.h"

GateData::GateData(const size_t &id, const float &x, const float &y) : _id
(id), _x(x), _y(y) { }

void GateData::addButtonNeeded(const size_t &id) {
    _buttons_needed.push_back(id);
}

void GateData::addEnergyReceiverNeeded(const size_t &id) {
    _energy_receivers_needed.push_back(id);
}

size_t GateData::getId() const {
    return _id;
}

float GateData::getX() const {
    return _x;
}

float GateData::getY() const {
    return _y;
}

const std::vector<size_t> &GateData::getButtonsNeeded() const {
    return _buttons_needed;
}

const std::vector<size_t> &GateData::getEnergyReceiversNeeded() const {
    return _energy_receivers_needed;
}
