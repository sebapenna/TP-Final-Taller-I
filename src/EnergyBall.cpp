#include "EnergyBall.h"
#include "constants.h"

EnergyBall::EnergyBall(b2Body *body, uint8_t direction) {
    _body = body;
    _direction = direction;
}

const float EnergyBall::getPositionX() {
    return _body->GetPosition().x;
}

const float EnergyBall::getPositiony() {
    return _body->GetPosition().y;
}
