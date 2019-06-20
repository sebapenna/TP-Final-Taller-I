#include "Cake.h"
#include "constants.h"

Cake::Cake(b2Body *body, const float& width, const float& height) : _body(body),
_width(width), _height(height), _chells_in_contact(0) { }

const uint8_t Cake::classId() {
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
    if (other->classId() == CHELL)
        ++_chells_in_contact;   // Chell llego a cake
}

void Cake::endCollitionWith(Collidable *other) {
    if (other->classId() == CHELL)
        --_chells_in_contact;   // Chell dejo posicion de cake
}

const float Cake::x() {
    return _body->GetPosition().x;
}

const float Cake::y() {
    return _body->GetPosition().y;
}

const float Cake::width() {
    return 0;
}

const float Cake::height() {
    return 0;
}

Cake::~Cake() = default;
