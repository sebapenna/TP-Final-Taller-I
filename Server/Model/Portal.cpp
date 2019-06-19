#include "Portal.h"
#include <Server/Model/constants.h>

Portal::Portal(const size_t&  id, b2Body *body, const b2Vec2 normal, const int16_t color) :
_body(body), _normal(normal), _color(color), _id(id) { }

const uint8_t Portal::getClassId() {
    return PORTAL_RAY;
}

void Portal::collideWith(Collidable *other) {

}

bool Portal::actedDuringStep() {
    return false;
}

void Portal::endCollitionWith(Collidable *other) {

}

const int16_t Portal::tilt() {
    if ((_normal.x > 0 && _normal.y >0) || (_normal.x < 0 && _normal.y < 0))
        return LEFT;    // Portal inclinado (rotado hacia izquierda)
    else if ((_normal.x > 0 && _normal.y < 0) || (_normal.x < 0 && _normal.y > 0))
        return RIGHT;   // Portal inclinado (rotado hacia derecha)
    else
        return STRAIGHT;    // Portal derecho
}

const int16_t Portal::color() const {
    return _color;
}

const size_t Portal::id() const {
    return _id;
}

b2Body *Portal::getBody() const {
    return _body;
}
