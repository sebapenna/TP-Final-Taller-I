#include "Rock.h"

Rock::Rock(b2Body *body) : _body(body){ }

float Rock::getPositionX() {
    return _body->GetPosition().x;
}

float Rock::getPositionY() {
    return _body->GetPosition().y;
}
