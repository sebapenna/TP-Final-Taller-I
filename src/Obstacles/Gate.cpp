#include "Gate.h"

bool Gate::isOpen() {
    return _open;
}

void Gate::addButtonNeeded(Button *button) {
    _buttons_needed.push_back(button);
}

void Gate::addEnergyReceiverNeeded(EnergyReceiver *e_receiver) {
    _energy_reveivers_needed.push_back(e_receiver);
}

void Gate::updateState() {
    if (_buttons_needed.empty() && _energy_reveivers_needed.empty())
        return; // Compuerta no tiene forma de abrir
    for (auto &it : _buttons_needed)
        if (!it->isActivated()) {
            _open = false;
            return;
        }
    for (auto &it : _energy_reveivers_needed)
        if (!it->isActivated()) {
            _open = false;
            return;
        }
    _open = true;   // Estaban todos activos
}

const std::string Gate::getClassName() {
    return GATE;
}

void Gate::collideWith(Collidable *other) {

}

void Gate::endCollitionWith(Collidable *other) {

}
