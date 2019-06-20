#include "Rock.h"
#include <Server/Model/constants.h>

Rock::Rock(const size_t &id, b2Body *body, const float& width, const float& height) : _body(body),
_id(id), _width(width), _height(height) {
    _previous_x = _body->GetPosition().x;
    _previous_y = _body->GetPosition().y;
}

bool Rock::isDead() const {
    return _dead;
}

b2Body *Rock::getBody() const {
    return _body;
}

void Rock::teletransport(float x, float y) {
    b2Vec2 new_pos(x,y);
    _body->SetTransform(new_pos, 0);
}

const uint8_t Rock::classId() {
    return ROCK;
}

void Rock::collideWith(Collidable *other) {
    auto c_name = other->classId();
    if (c_name == ENERGY_BARRIER) {
        _dead = true;
    }
}

void Rock::endCollitionWith(Collidable *other) {
    // No realiza ninguna accion ante fin de colision
}

bool Rock::actedDuringStep() {
    if (_previously_dead != _dead) {
        _previously_dead = _dead;   // Se debe eliminar roca
        return true;
    }
    // Calculo diferencia para evitar detectar cambio de posicion menor a delta
    float diff_x = abs(_previous_x - _body->GetPosition().x);
    float diff_y = abs(_previous_y - _body->GetPosition().y);
    if (diff_x > DELTA_POS || diff_y > DELTA_POS) {
        _previous_x = _body->GetPosition().x;
        _previous_y = _body->GetPosition().y;
        return true;    // Se movio
    }
    return false;
}

const size_t Rock::id() const {
    return _id;
}

const float Rock::x() {
    return _body->GetPosition().x;
}

const float Rock::y() {
    return _body->GetPosition().y;
}

const float Rock::width() {
    return _width;
}

const float Rock::height() {
    return _height;
}

float Rock::velocityY() {
    return _body->GetLinearVelocity().y;
}

Rock::~Rock() = default;

