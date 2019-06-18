#include "Cake.h"
#include "constants.h"

Cake::Cake(b2Body *body) : _body(body), _chells_in_contact(0) { }

const uint8_t Cake::getClassId() {
    return CAKE;
}

float Cake::getX() {
    return _body->GetPosition().x;
}

float Cake::getY() {
    return _body->GetPosition().y;
}

bool Cake::actedDuringStep() {
    return false;   // No realiza accion en el juego
}

void Cake::collideWith(Collidable *other) {
    if (other->getClassId() == CHELL)
        ++_chells_in_contact;   // Chell llego a cake
}

void Cake::endCollitionWith(Collidable *other) {
    if (other->getClassId() == CHELL)
        --_chells_in_contact;   // Chell dejo posicion de cake
}

size_t Cake::getNumberOfChellsInContact() const {
    return _chells_in_contact;
}
