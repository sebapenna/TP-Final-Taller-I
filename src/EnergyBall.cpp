#include "EnergyBall.h"
#include <src/constants.h>

EnergyBall::EnergyBall(b2Body *body, uint8_t direction) {
    _body = body;
    int x_impulse = 0, y_impulse = 0;
    switch (direction) {
        case O_N:
            y_impulse = ENRG_BALL_FORCE;
            break;
        case O_S:
            y_impulse = -1 * ENRG_BALL_FORCE;
            break;
        case O_E:
            x_impulse = ENRG_BALL_FORCE;
            break;
        case O_O:
            x_impulse = -1 * ENRG_BALL_FORCE;
            break;
        default:    // No existe este caso
            break;
    }
    b2Vec2 impulse(x_impulse, y_impulse);
    _body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
}

void EnergyBall::updateLifetime() {
    _lifetime += TIME_STEP;
    float diff_time = ENERGY_BALL_MAX_LIFETIME - _lifetime;
    if (diff_time < TIME_STEP) {
        _dead = true;
        _kill = true;   // Indico que se debe eliminar
    }
}

bool EnergyBall::isDead() {
    return _dead;
}

const float EnergyBall::getPositionX() {
    return _body->GetPosition().x;
}

const float EnergyBall::getPositionY() {
    return _body->GetPosition().y;
}

const std::string EnergyBall::getClassName() {
    return ENERGY_BALL;
}

b2Body *EnergyBall::getBody() const {
    return _body;
}

void EnergyBall::collideWith(Collidable *other) {
    auto c_name = other->getClassName();
    if (c_name == ROCK_BLOCK || c_name == ACID || c_name == BUTTON ||
        c_name == ROCK || c_name == ENERGY_RECEIVER || c_name == CHELL ||
        c_name == PIN_TOOL) {
        if (!_dead)
            _kill = true;   // Debo eliminar energy ball
        _dead = true;
    } else if (c_name == ENERGY_TRANSMITTER && _lifetime != 0) {
        if (!_dead)
            _kill = true;   // Debo eliminar energy ball
        _dead = true;    // Verifico que no colisiona cuando se crea la bola
    }
}

void EnergyBall::endCollitionWith(Collidable *other) {

}

bool EnergyBall::kill() const {
    return _kill;
}

void EnergyBall::killed() {
    _kill = false;
}
