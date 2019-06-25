#include "Cake.h"
#include "Server/Model/constants.h"

Cake::Cake(b2Body *body, const float& width, const float& height) : _body(body),
_width(width), _height(height), _chells_in_contact(0) { }

const uint8_t Cake::classId() {
    return CAKE;
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
    return _width;
}

const float Cake::height() {
    return _height;
}

void Cake::step(const float &time_step) {
    // No realiza accion en step
}

bool Cake::isDead(const float &time_step) {
    return false;   // No se destruye
}

b2Body *Cake::getBody() const {
    return _body;
}

size_t Cake::getChellsInContact() const {
    return _chells_in_contact;
}

Cake::~Cake() = default;
