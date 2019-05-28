#include "Chell.h"
#include "constants.h"
#include "exceptions.h"

Chell::Chell(unsigned int id, b2Body *body) : _id(id){
    _body = body;
    _move_state = MOVE_STOP;
    _jump_state = ON_GROUND;
    _jump = false;
}

const unsigned int Chell::getId() const {
    return _id;
}

float Chell::getPositionX() {
    return  _body->GetPosition().x;
}

float Chell::getPositionY() {
    return  _body->GetPosition().y;
}

void Chell::move_left() {
    _move_state = MOVE_LEFT;
}

void Chell::move_right() {
    _move_state = MOVE_RIGHT;
}

void Chell::jump() {
    if (_jump_state == ON_GROUND)
        _jump = true;
    else
        throw ChellNotOnGroundException();
}

void Chell::stop_movement() {
    _move_state = MOVE_STOP;
}

void Chell::teletransport(float x, float y) {
    b2Vec2 new_pos(x,y);
    _body->SetTransform(new_pos, 0);
}

void Chell::updateJumpState() {
    float vel_y = _body->GetLinearVelocity().y;
    switch (_jump_state) {
        case ON_GROUND:
            if (vel_y > DELTA_Y_VEL)
                _jump_state = JUMPING;
            else if (vel_y < 0)  // Cuerpo cayo de una superficie
                _jump_state = FALLING;
            break;
        case JUMPING:
            if (vel_y <= 0) // Empieza a caer
                _jump_state = FALLING;
            break;
        case FALLING:
            if (abs(vel_y) < DELTA_Y_VEL)
                _jump_state = ON_GROUND;  // Cae en una superficie
            break;
    }
}

bool Chell::movementAlreadyApplied() {
    float vel_x = _body->GetLinearVelocity().x;
    if (_move_state == MOVE_RIGHT && vel_x > 0)    // Moviendo hacia derecha
        return true;
    if (_move_state == MOVE_LEFT && vel_x < 0)  // Moviendo hacia izquierda
        return true;
    return (_move_state == MOVE_STOP && vel_x == 0);    // Cuerpo quieto
}

int Chell::calculateXImpulse() {
    if (movementAlreadyApplied()) // _move_state no se modifico
        return 0;
    float vel_x = _body->GetLinearVelocity().x;
    int impulse_factor = 0;
    // Cuando se mueve en un sentido factor sera el doble, para frenarlo y
    // luego seguir moviendose en sentido contrario
    switch (_move_state) {
        case MOVE_RIGHT:
            (vel_x < 0) ? (impulse_factor = 2) : (impulse_factor = 1);
            break;
        case MOVE_LEFT:
            (vel_x > 0) ? (impulse_factor = -2) : (impulse_factor = -1);
            break;
        case MOVE_STOP:
            if (_jump_state == ON_GROUND) // Verifico que no este en aire
                (vel_x > 0) ? (impulse_factor = -1) : (impulse_factor = 1);
            break;
        default: // No existe este caso
            break;
    }
    return impulse_factor * MOVE_FORCE;
}

void Chell::move() {
    int x_impulse = 0, y_impulse = 0;
    x_impulse = calculateXImpulse();
    if (_jump) {
        _jump = false;
        y_impulse = MOVE_FORCE;
    }
    b2Vec2 impulse(x_impulse, y_impulse);
    _body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
    updateJumpState();
}
