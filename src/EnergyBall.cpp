#include "EnergyBall.h"
#include "constants.h"

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

const float EnergyBall::getPositionX() {
    return _body->GetPosition().x;
}

const float EnergyBall::getPositionY() {
    return _body->GetPosition().y;
}
