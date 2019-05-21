#include "chell.h"
#include "constants.h"

Chell::Chell(unsigned int id, b2Body *body) : _id(id){
    _body = body;
    move_state = MOVE_STOP;
    _jumping = false;
}

const unsigned int Chell::getId() const {
    return _id;
}

void Chell::move_left() {
    move_state = MOVE_LEFT;
}

void Chell::move_right() {
    move_state = MOVE_RIGHT;
}

void Chell::stop_movement() {
    move_state = MOVE_STOP;
}

void Chell::jump() {
    b2ContactEdge * ctc = _body->GetContactList();
    if (ctc) // Chell esta en contacto con una superficie, suficiente una
        _jumping = true;
}

void Chell::teletransport(float x, float y) {
    b2Vec2 new_pos(x,y);
    _body->SetTransform(new_pos, 0);
}

void Chell::move() {
    int x_impulse = 0;
    int y_impulse = 0;
    switch (move_state) {
        case MOVE_RIGHT:
            x_impulse = MOVE_FORCE;
            break;
        case MOVE_LEFT:
            x_impulse = -1 * MOVE_FORCE;
            break;
        case MOVE_STOP:
            x_impulse = 0;
            break;
        default: // No existe este caso
            break;
    }
    if (_jumping) {
        y_impulse = MOVE_FORCE;
        _jumping = false; // todo: ok setearlo false aca?
    }
    b2Vec2 impulse(x_impulse, y_impulse);
    _body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
}

float Chell::getX() {
    return  _body->GetPosition().x;
}

float Chell::getY() {
    return  _body->GetPosition().y;
}
