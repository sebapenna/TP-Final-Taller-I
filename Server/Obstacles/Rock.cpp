#include "Rock.h"
#include <Server/constants.h>

Rock::Rock(b2Body *body) : _body(body){
    _previous_x = _body->GetPosition().x;
    _previous_y = _body->GetPosition().y;
}

float Rock::getPositionX() {
    return _body->GetPosition().x;
}

float Rock::getPositionY() {
    return _body->GetPosition().y;
}

float Rock::getVelocityY() {
    return _body->GetLinearVelocity().y;
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

const std::string Rock::getClassName() {
    return ROCK;
}

void Rock::collideWith(Collidable *other) {
    auto c_name = other->getClassName();
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
    if (_previous_x != _body->GetPosition().x || _previous_y != _body->GetPosition().y) {
        _previous_x = _body->GetPosition().x;
        _previous_y = _body->GetPosition().y;
        return true;    // Se movio
    }
    return false;
}

