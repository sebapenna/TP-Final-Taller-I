#include "Portal.h"
#include <Server/Model/constants.h>

Portal::Portal(const size_t&  id, b2Body *body, const b2Vec2 normal, const int16_t color,
               const float& width, const float& height) :
_body(body), _normal(normal), _color(color), _id(id), _width(width), _height(height) { }

const uint8_t Portal::classId() {
    return PORTAL;
}

void Portal::collideWith(Collidable *other) {

}

bool Portal::actedDuringStep() {
    return false;
}

void Portal::endCollitionWith(Collidable *other) {

}

const int16_t Portal::tilt() {
    if ((_normal.x > 0 && _normal.y > 0) || (_normal.x < 0 && _normal.y < 0))
        return LEFT;    // Portal inclinado (rotado hacia izquierda)
    else if ((_normal.x > 0 && _normal.y < 0) || (_normal.x < 0 && _normal.y > 0))
        return RIGHT;   // Portal inclinado (rotado hacia derecha)
    else
        return STRAIGHT;    // Portal derecho
}

const int16_t Portal::colour() const {
    return _color;
}

const size_t Portal::id() const {
    return _id;
}

b2Body *Portal::getBody() const {
    return _body;
}

const float Portal::getWidth() const {
    return _width;
}

const float Portal::getHeight() const {
    return _height;
}

const b2Vec2 &Portal::normal() const {
    return _normal;
}

void Portal::setExitPortal(Portal *other) {
    if (other)
        _exit_portal = other;
}

Portal *Portal::exitPortal() const {
    return _exit_portal;
}

const float Portal::x() {
    return _body->GetPosition().x;
}

const float Portal::y() {
    return _body->GetPosition().y;
}

const float Portal::width() {
    return _width;
}

const float Portal::height() {
    return _height;
}
