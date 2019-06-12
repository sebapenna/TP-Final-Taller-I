#include "Chell.h"
#include <Server/Model/constants.h>
#include <Common/exceptions.h>
#include <Server/Model/Obstacles/Rock.h>
#include <Server/Model/GroundBlocks/MetalDiagonalBlock.h>

Chell::Chell(const size_t &id, b2Body *body) : _id(id){
    _body = body;
    _move_state = MOVE_STOP;
    _jump_state = ON_GROUND;
    _jump = false;
    _dead = false;
    _previous_tilt = NOT_TILTED;
    _tilt = NOT_TILTED;
    _previous_x = _body->GetPosition().x;
    _previous_y = _body->GetPosition().y;
}

const size_t Chell::getId() const {
    return _id;
}

float Chell::getX() {
    return  _body->GetPosition().x;
}

float Chell::getY() {
    return  _body->GetPosition().y;
}

bool Chell::isDead() {
    return _dead;
}

b2Body *Chell::getBody() const {
    return _body;
}

int16_t Chell::tilt() const {
    return _tilt;
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
//    else
//        throw ChellNotOnGroundException();
}

void Chell::stopMovement() {
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
                _jump_state = JUMPED;
            else if (vel_y < 0 && abs(vel_y) > DELTA_Y_VEL)  // Cuerpo cayo de una superficie
                _jump_state = FALLING;
            break;
        case JUMPED:
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

const uint8_t Chell::getClassId() {
    return CHELL;
}

void Chell::collideWith(Collidable *other) {
    auto cname = other->getClassId();
    if (cname == ROCK ) {
        auto rock = (Rock*) other;
        float head_pos = this->getY() + CHELL_HALF_HEIGHT;
        // Verifico esta por encima de chell y cayendo
        if (rock->getY() > head_pos && rock->getVelocityY() != 0)
            _dead = true;
    } else if (cname == ACID || cname == ENERGY_BALL) {
        _dead = true;
    } else if (cname == METAL_DIAGONAL_BLOCK) {
        auto block = (MetalDiagonalBlock*) other;
        switch (block->getOrientation()) {
            case O_NE:
                _tilt = EAST;
                break;
            case O_NO:
                _tilt = WEST;
                break;
            default:    // Chell no se inclina
                break;
        }
    }
}

void Chell::endCollitionWith(Collidable *other) {
    if (other->getClassId() == METAL_DIAGONAL_BLOCK)
        _tilt = NOT_TILTED;   // Deja de caminar en diagonal
}

bool Chell::actedDuringStep() {
    if (_previously_dead != _dead){
        _previously_dead = _dead;   // Chell murio en ultimo step
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
    if (_previous_tilt != _tilt) {
        _previous_tilt = _tilt;
        return true;
    }
    if (_previously_carrying != _carrying_rock) {
        _previously_carrying = _carrying_rock;
        return true;
    }
    // Retorno ultima condicion, shooting no cambio estado porque es solo un instante,
    // y se actualiza llamando a isShooting();
    return _shooting;
}

bool Chell::isShooting() {
    if (_shooting) {
        _shooting = false;
        return true;
    }
    return false;
}

bool Chell::isJumping() {
    return _jump_state != ON_GROUND;
}

bool Chell::isMoving() {
    return (_body->GetLinearVelocity().x != 0);
}

uint8_t Chell::movementDirection() {
    if (_body->GetLinearVelocity().x < 0)
        return O_O;
    return O_E;
}

bool Chell::isCarryingRock() {
    return _carrying_rock;
}

