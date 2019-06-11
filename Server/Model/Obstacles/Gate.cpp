#include "Gate.h"

Gate::Gate(const size_t &id, const float& x, const float& y) :_id(id), _x(x), _y(y) { }

bool Gate::isOpen() {
    return _open;
}

const size_t Gate::getId() const {
    return _id;
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

const uint8_t Gate::getClassId() {
    return GATE;
}

void Gate::collideWith(Collidable *other) {
    // No realiza ninguna accion ante colision
}

void Gate::endCollitionWith(Collidable *other) {
    // No realiza ninguna accion ante fin de colision
}

bool Gate::actedDuringStep() {
    if (_previously_open != _open) {
        _previously_open = _open;  // Seteo booleano para evitar detectar falso cambio de estado
        return true;
    }
    return false;
}


const float Gate::getX() const {
    return _x;
}

const float Gate::getY() const {
    return _y;
}
