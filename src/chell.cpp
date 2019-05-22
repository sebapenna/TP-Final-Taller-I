#include <iostream>
#include "chell.h"
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

float Chell::getX() {
    return  _body->GetPosition().x;
}

float Chell::getY() {
    return  _body->GetPosition().y;
}

void Chell::move_left() {
    _move_state = MOVE_LEFT;
}

void Chell::move_right() {
    _move_state = MOVE_RIGHT;
}

void Chell::stop_movement() {
    _move_state = MOVE_STOP;
}

void Chell::jump() {
    if (_jump_state == ON_GROUND)
        _jump = true;
    else
        throw ChellNoEstaSobreSuperficieDondeSaltarException();
}

void Chell::teletransport(float x, float y) {
    b2Vec2 new_pos(x,y);
    _body->SetTransform(new_pos, 0);
}

bool Chell::forceAlreadyApplied() {
    float vel_x = _body->GetLinearVelocity().x;
    if (_move_state == MOVE_RIGHT && vel_x > 0)    // Moviendo hacia derecha
        return true;
    return (_move_state == MOVE_LEFT && vel_x < 0);  // Moviendo hacia izquierda
}

void Chell::updateJumpState() {
    float vel_y = _body->GetLinearVelocity().y;
    switch (_jump_state) {
        case FALLING:
            if (abs(vel_y) < DELTA_Y_VEL)   // Ya no tiene velocidad en eje y
                _jump_state = ON_GROUND;
            break;
        case JUMPING:
            if (vel_y <= 0) // Empieza a caer
                _jump_state = FALLING;
            else if (abs(vel_y) < DELTA_Y_VEL)
                _jump_state = ON_GROUND;    // Salta y cae en otra superficie
            break;
        case ON_GROUND:
            if (vel_y < 0)  // Cuerpo cayo de una superficie
                _jump_state = FALLING;
    }
}

uint8 Chell::lastMovement() {
    if (_body->GetLinearVelocity().x > 0)
        return MOVE_RIGHT;
    if (_body->GetLinearVelocity().x < 0)
        return MOVE_LEFT;
    return MOVE_STOP;
}

void Chell::move() {
    int x_impulse = 0, y_impulse = 0;
    switch (_move_state) {
        case MOVE_RIGHT:
            x_impulse = MOVE_FORCE;
            break;
        case MOVE_LEFT:
            x_impulse = -1 * MOVE_FORCE;
            break;
        case MOVE_STOP:
            if (_jump_state == ON_GROUND) { // Verifico que no este en aire
                uint8 last_movement = lastMovement();
                if (last_movement == MOVE_RIGHT)
                    x_impulse = -1 * MOVE_FORCE;
                else if (last_movement == MOVE_LEFT)
                    x_impulse = MOVE_FORCE;
            }
            break;
        default:
            break;
    }
    if (_jump) {
        _jump = false;
        _jump_state = JUMPING;
        y_impulse = MOVE_FORCE;
    }
    b2Vec2 impulse(x_impulse, y_impulse);
    std::cout << "velx: " <<_body->GetLinearVelocity().x << " ";
    std::cout << "vely: " <<_body->GetLinearVelocity().y << " ";
    if (!forceAlreadyApplied()) // Aplico fuerza solo si esta quieto
        _body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
    updateJumpState();
}
