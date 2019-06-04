#include "Rock.h"
#include <src/constants.h>

Rock::Rock(b2Body *body) : _body(body){ }

float Rock::getPositionX() {
    return _body->GetPosition().x;
}

float Rock::getPositionY() {
    return _body->GetPosition().y;
}

void Rock::teletransport(float x, float y) {
    b2Vec2 new_pos(x,y);
    _body->SetTransform(new_pos, 0);
}

void Rock::collideWith(Collidable *other) {

}

const std::string Rock::getClassName() {
    return ROCK;
}

void Rock::endCollitionWith(Collidable *other) {

}
