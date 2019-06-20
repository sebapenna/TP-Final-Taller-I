#include "Chell.h"
#include <Server/Model/constants.h>
#include <Common/exceptions.h>
#include <Server/Model/Obstacles/Rock.h>
#include <Server/Model/GroundBlocks/MetalDiagonalBlock.h>
#include <Server/Model/Obstacles/Acid.h>

Chell::Chell(const size_t &id, b2Body *body, const float& width, const float& height) : _id(id),
_body(body), _move_state(MOVE_STOP), _jump_state(ON_GROUND), _previous_jump_state(ON_GROUND),
_jump(false), _dead(false), _previously_dead(false), _carrying_rock(false), _previously_carrying
(false), _shooting(false), _hit_wall(false), _reached_cake(false), _previous_tilt(NOT_TILTED),
_tilt(NOT_TILTED), _width(width), _height(height) {
    _previous_x = _body->GetPosition().x;
    _previous_y = _body->GetPosition().y;
    _portals.first = nullptr;   // Seteo a null ambos portales
    _portals.second = nullptr;
}

const float Chell::x() {
    return  _body->GetPosition().x;
}

const float Chell::y() {
    return  _body->GetPosition().y;
}

const float Chell::width() {
    return _width;
}

const float Chell::height() {
    return _height;
}

const size_t Chell::id() const {
    return _id;
}

bool Chell::isDead() {
    return _dead;
}

b2Body *Chell::getBody() const {
    return _body;
}

const uint8_t Chell::classId() {
    return CHELL;
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
    else
        throw ChellNotOnGroundException();
}

void Chell::stopMovement() {
    _move_state = MOVE_STOP;
}

void Chell::teleport(float x, float y) {
    b2Vec2 new_pos(x,y);
    _body->SetTransform(new_pos, 0);
}

bool Chell::reachedCake() {
    return _reached_cake;
}

void Chell::kill() {
    _dead = true;
}

int Chell::setNewPortal(Portal *portal) {
    size_t old_portal_id = -1;
    if (portal->colour() == ORANGE_PORTAL) {
        if (_portals.first)
            old_portal_id = _portals.first->id();
        if (_portals.second)
            portal->setExitPortal(_portals.second);  // Seteo portal de salida
        _portals.first = portal;
    } else {
        if (_portals.second)
            old_portal_id = _portals.second->id();
        if (_portals.first)
            portal->setExitPortal(_portals.first);  // Seteo portal de salida
        _portals.second = portal;
    }
    return old_portal_id;
}

void Chell::updateJumpState() {
    float vel_y = _body->GetLinearVelocity().y;
    switch (_jump_state) {
        case ON_GROUND:
            if (_tilt == NOT_TILTED) {  // Si esta en bloque diagonal sigue en tierra
                if (vel_y > DELTA_VEL)
                    _jump_state = JUMPED;
                else if (vel_y < 0 && abs(vel_y) > DELTA_VEL)  // Cuerpo cayo de una superficie
                    _jump_state = FALLING;
            }
            break;
        case JUMPED:
            if (vel_y <= 0)  // Empieza a caer
                _jump_state = FALLING;
            break;
        case FALLING:
            if (abs(vel_y) < DELTA_VEL)
                _jump_state = ON_GROUND;  // Cae en una superficie
            break;
    }
}

bool Chell::movementInXAlreadyApplied() {
    float vel_x = _body->GetLinearVelocity().x;
    if (_move_state == MOVE_RIGHT && vel_x > 0)    // Moviendo hacia derecha
        return true;
    if (_move_state == MOVE_LEFT && vel_x < 0)  // Moviendo hacia izquierda
        return true;
    return (_move_state == MOVE_STOP && vel_x == 0 && !_hit_wall);    // Cuerpo quieto
}

int Chell::calculateXImpulse() {
    if (movementInXAlreadyApplied()) // _move_state no se modifico
        return 0;
    float vel_x = _body->GetLinearVelocity().x;
    int impulse_factor = 0;
    // Mover en sentido contrario tendra factor doble, para frenar y continuar movimiento
    switch (_move_state) {
        case MOVE_RIGHT:
            (vel_x < 0) ? (impulse_factor = 2) : (impulse_factor = 1);
            break;
        case MOVE_LEFT:
            (vel_x > 0) ? (impulse_factor = -2) : (impulse_factor = -1);
            break;
        case MOVE_STOP:
            if (vel_x > 0)
                impulse_factor = -1;
            else if (vel_x < 0)
                impulse_factor = 1;
            break;
        default: // No existe este caso
            break;
    }
    return impulse_factor * MOVE_FORCE;
}

void Chell::move() {
    if (_portal_to_use) {   // Chell se debe teletransportar
        float newx = _portal_to_use->exitPortal()->x();
        float newy = _portal_to_use->exitPortal()->y();
        float new_velx = x() * _portal_to_use->exitPortal()->normal().x;
        float new_vely = y() * _portal_to_use->exitPortal()->normal().y;
        teleport(newx, newy);
        _body->SetLinearVelocity({new_velx, new_vely});
        _portal_to_use = nullptr;   // Teletransportacion realizada
        _teleported = true; // Indico que chell se teletransporto durante step
    }
    if (_tilt == NOT_TILTED) {
        int x_impulse = 0, y_impulse = 0;
        x_impulse = calculateXImpulse();
        if (_jump) {
            _jump = false;
            y_impulse = JUMP_FORCE;
        }
        b2Vec2 impulse(x_impulse, y_impulse);
        _body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
    }
    updateJumpState();
}

bool Chell::actedDuringStep() {
    if (_previously_dead != _dead) {
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
    if (_hit_wall)
        return true;
    if (_previous_tilt != _tilt) {
        _previous_tilt = _tilt;
        return true;
    }
    if (_previous_jump_state != _jump_state) {
        _previous_jump_state = _jump_state;
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

void Chell::collideWith(Collidable *other) {
    auto cname = other->classId();
    if (cname == ROCK) {
        auto rock = (Rock*) other;
        float head_pos = this->y() + CHELL_HALF_HEIGHT;
        // Evaluo si esta encima de chell y cayendo
        (rock->y() > head_pos && rock->velocityY() != 0) ? _dead = true : _hit_wall = true;
    } else if (cname == ACID || cname == ENERGY_BALL) {
        _dead = true;
    } else if (cname == METAL_DIAGONAL_BLOCK) {
        _hit_wall = true;
        auto block = (MetalDiagonalBlock*) other;
        auto diff_x = abs(x() - block->x());
        switch (block->getOrientation()) {
            case O_NE:
                if (_body->GetLinearVelocity().x < 0 ||
                        (abs(_body->GetLinearVelocity().y) > DELTA_VEL && diff_x < CHELL_HALF_WIDTH)) {
                    // De costado o arriba
                    _tilt = EAST;   //todo: lo mismo en O_NO
                }
                break;
            case O_NO:
                if (_body->GetLinearVelocity().x > 0 || abs(_body->GetLinearVelocity().y) >
                DELTA_VEL) {    // De costado o arriba
                    _tilt = WEST;
                    _body->ApplyLinearImpulse({-2 * MOVE_FORCE, 0},
                                              _body->GetWorldCenter(), true);
                }
                break;
            default:    // Chell no se inclina
                break;
        }
    } else if (cname == ROCK_BLOCK || cname == METAL_BLOCK || cname == GATE || cname == CAKE ||
    cname == ENERGY_RECEIVER || cname == ENERGY_TRANSMITTER) {
        if (abs(_body->GetLinearVelocity().y) > DELTA_VEL ||
        abs(_body->GetLinearVelocity().x) > DELTA_VEL) {    // Verifico no sea velocidad error delta
            _hit_wall = true;
            _move_state = MOVE_STOP;    // Freno cuando colisiona con bloque (saltando o caminando)
        }
        if (cname == CAKE)
            _reached_cake = true;
    } else if (cname == PORTAL) {
        if (!_teleported) {
            auto portal = (Portal *) other;
            if (portal->exitPortal())   // Verifico que tenga ambos portales
                _portal_to_use = portal;
            else
                _hit_wall = true;
        }   // Si se teletransporto se ignorara contacto en pre-solve
    }
}

void Chell::endCollitionWith(Collidable *other) {
    auto cname = other->classId();
    if (cname == METAL_DIAGONAL_BLOCK) {
        if (_tilt != NOT_TILTED)
            _body->SetLinearVelocity({0,0});
        _tilt = NOT_TILTED;   // Deja de caminar en diagonal
    } else if (cname == ROCK_BLOCK || cname == METAL_BLOCK || cname == ROCK ||
    cname == ENERGY_RECEIVER || cname == ENERGY_TRANSMITTER) {
        _hit_wall = false;
    } else if (cname == CAKE) {
        _hit_wall = false;
        _reached_cake = false;
    } else if(cname == PORTAL) {
        if (!_teleported)
            _hit_wall = false;
    }
}

bool Chell::ifTeleportedSetDone() {
    if (_teleported) {
        _teleported = false;    // Chell ya realizo teletransportacion
        return true;
    }
    return false;
}
