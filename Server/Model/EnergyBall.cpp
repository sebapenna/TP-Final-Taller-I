#include "EnergyBall.h"
#include <Server/Model/constants.h>

EnergyBall::EnergyBall(const size_t &id, b2Body *body, uint8_t direction) : _id(id) {
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
    _previous_x = _body->GetPosition().x;
    _previous_y = _body->GetPosition().y;
}

void EnergyBall::updateLifetime() {
    _lifetime += TIME_STEP;
}

bool EnergyBall::isDead() {
    float diff_time = ENERGY_BALL_MAX_LIFETIME - _lifetime;
    return (_dead || diff_time < TIME_STEP);
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

size_t EnergyBall::getId() const {
    return _id;
}

void EnergyBall::collideWith(Collidable *other) {
    auto c_name = other->getClassName();
    if (c_name == ROCK_BLOCK || c_name == ACID || c_name == BUTTON ||
        c_name == ROCK || c_name == ENERGY_RECEIVER || c_name == CHELL ||
        c_name == PIN_TOOL) {
        _dead = true;
    } else if (c_name == ENERGY_TRANSMITTER && _lifetime != 0) {
        _dead = true;    // Verifico que no colisiona cuando se crea la bola
    }
}

void EnergyBall::endCollitionWith(Collidable *other) {

}

bool EnergyBall::actedDuringStep() {
    if (_previously_dead != _dead) {
        _previously_dead = _dead;
        return true;
    }
    // Calculo diferencia para evitar detectar cambio de posicion menor a delta
    float diff_x = abs(_previous_x - _body->GetPosition().x);
    float diff_y = abs(_previous_y - _body->GetPosition().y);
    if (diff_x > DELTA_POS || diff_y > DELTA_POS) {
        _previous_x = _body->GetPosition().x;
        _previous_y = _body->GetPosition().y;
        return true;
    }
    return false;
}
