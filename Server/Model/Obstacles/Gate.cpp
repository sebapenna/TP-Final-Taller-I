#include <Box2D/Dynamics/b2Body.h>
#include <Server/Model/Chell.h>
#include "Gate.h"

Gate::Gate(const size_t &id, b2Body *body, const float& width, const float& height) :_id(id),
_body(body), _width(width), _height(height) { }

bool Gate::isOpen() {
    return _open;
}

const size_t Gate::id() const {
    return _id;
}

void Gate::addButtonNeeded(Button *button) {
    _buttons_needed.push_back(button);
}

void Gate::addEnergyReceiverNeeded(EnergyReceiver *e_receiver) {
    _energy_reveivers_needed.push_back(e_receiver);
}

const uint8_t Gate::classId() {
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

const float Gate::x() {
    return _body->GetPosition().x;
}

const float Gate::y() {
    return _body->GetPosition().y;
}

const float Gate::width() {
    return _width;
}

const float Gate::height() {
    return _height;
}

void Gate::verifyChellsUnderIt() {
    for (auto it = _body->GetContactList(); it; it = it->next) {
        auto coll1 = (Collidable*) it->contact->GetFixtureA()->GetBody()->GetUserData();
        auto coll2 = (Collidable*) it->contact->GetFixtureB()->GetBody()->GetUserData();
        Chell *chell;
        if (coll1->classId() == CHELL || coll2->classId() == CHELL) {
            Chell* chell = nullptr;
            if (coll1->classId() == CHELL)
                chell = (Chell*) coll1;
            else
                chell = (Chell*) coll2;
            if (((chell->x() > x() - _width/2) || (chell->x() < x() + _width/2))
                && (chell->y() < y() + _height/2))
                chell->kill();  // Compuerta la aplasta
        }
    }
}

void Gate::step(const float &time_step) {
    if (_buttons_needed.empty() && _energy_reveivers_needed.empty())
        return; // Compuerta no tiene forma de abrir
    for (auto &it : _buttons_needed)
        if (!it->isActivated()) {
            if (_open)  // Compuerta pasa de abierta a cerrada
                verifyChellsUnderIt();
            _open = false;
            return;
        }
    for (auto &it : _energy_reveivers_needed)
        if (!it->isActivated()) {
            if (_open)  // Compuerta pasa de abierta a cerrada
                verifyChellsUnderIt();
            _open = false;
            return;
        }
    _open = true;   // Estaban todos activos
}

bool Gate::isDead(const float &time_step) {
    return false;   // No se destruye
}

b2Body *Gate::getBody() const {
    return _body;
}

Gate::~Gate() = default;
