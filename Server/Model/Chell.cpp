#include "Chell.h"
#include <Server/Model/constants.h>
#include <Common/exceptions.h>
#include <Server/Model/Obstacles/Rock.h>
#include <Server/Model/GroundBlocks/MetalDiagonalBlock.h>
#include <Server/Model/Obstacles/Acid.h>

Chell::Chell(const size_t &id, b2Body *body, const float& width, const float& height) : _id(id),
_body(body), _move_state(MOVE_STOP), _jump_state(ON_GROUND), _previous_jump_state(ON_GROUND),
_jump(false), _dead(false), _shooting(false), _hit_wall(false), _reached_cake(false),
_previous_tilt(NOT_TILTED),_tilt(NOT_TILTED), _width(width), _height(height) {
    _previous_x = _body->GetPosition().x;
    _previous_y = _body->GetPosition().y;
    _portals.first = nullptr;   // Seteo a null ambos portales
    _portals.second = nullptr;
}

Chell::~Chell() = default;

void Chell::setJumpForce(float jumpForce) {
    _jump_force = jumpForce;
}

void Chell::setMoveForce(float moveForce) {
    _move_force = moveForce;
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

bool Chell::isDead(const float &time_step) {
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
    auto it = _body->GetContactList();
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
    // todo: calculo velocidad al salir
    float impulse_x = 2 *_move_force * _portal_to_use->exitPortal()->normal().x;

    float impulse_y = 1.5*_move_force * _portal_to_use->exitPortal()->normal().y;
    b2Vec2 new_pos(x,y);
    _body->SetTransform(new_pos, 0);
    (_jump_state != ON_GROUND) ? (_jump_state = ON_GROUND) : 0;
    _body->SetLinearVelocity({0,0});    // Anulo velocidad que tenia
    _body->ApplyLinearImpulse({impulse_x, impulse_y}, _body->GetWorldCenter(), true);
}

bool Chell::reachedCake() {
    return _reached_cake;
}

void Chell::kill() {
    _dead = true;
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
        case FALLING:   // Velocidad menor a delta o no mas inclinado
            if (abs(vel_y) < DELTA_VEL || (_tilt != NOT_TILTED))
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
    return (_move_state == MOVE_STOP && vel_x == 0 && _hit_wall);    // Cuerpo quieto
}

int Chell::calculateXImpulse() {
    if (movementInXAlreadyApplied()) // _move_state no se modifico
        return 0;
    float vel_x = _body->GetLinearVelocity().x;
    float vel_y = _body->GetLinearVelocity().y;
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
            if (_jump_state == ON_GROUND) {   // Stop en superficie frena cuerpo, mantengo vely
                _body->SetLinearVelocity({0, vel_y});
            }
            if (_jump_state == JUMPED) {    // En el aire realiza impulso, no frena cuerpo
                if (vel_x > 0)
                    impulse_factor = -1;
                else if (vel_x < 0)
                    impulse_factor = 1;
            }
            break;
        default: // No existe este caso
            break;
    }
    return impulse_factor * _move_force;
}

void Chell::move() {
    if (_portal_to_use) {   // Chell se debe teletransportar
        float newx = _portal_to_use->exitPortal()->x();
        float newy = _portal_to_use->exitPortal()->y();
        teleport(newx, newy);
        _portal_to_use = nullptr;   // Teletransportacion realizada
        _teleported = true; // Indico que chell se teletransporto durante step
    } else if (_tilt == NOT_TILTED) {  // Si esta inclinado cae, no se mueve
        int x_impulse = 0, y_impulse = 0;
        x_impulse = calculateXImpulse();
        if (_jump) {
            _jump = false;
            y_impulse = _jump_force;
        }
        b2Vec2 impulse(x_impulse, y_impulse);
        _body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
    }
    updateJumpState();
}

bool Chell::actedDuringStep() {
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
    // Retorno ultima condicion, shooting no cambio estado porque es solo un instante,
    // y se actualiza llamando a isShooting();
    if (_previously_shooting != _shooting) {
        _previously_shooting = _shooting;
        return true;
    }
    return false;
}

void Chell::collideWith(Collidable *other) {
    auto cname = other->classId();
    auto velx = _body->GetLinearVelocity().x;
    auto vely = _body->GetLinearVelocity().y;
    if (cname == METAL_DIAGONAL_BLOCK) {
        _hit_wall = true;
        auto block = (MetalDiagonalBlock*) other;
        switch (block->getOrientation()) {
            case O_NE:
                // Evaluo si esta moviendose hacia izquierda o si la velocidad en Y es mayor que
                // delta. Siempre chell debe estar a partir del centro del bloque para inclinarse
                if ((velx < 0 || abs(vely) > DELTA_VEL) && (x() > block->getCenterX()) && !_teleported)
                    _tilt = EAST;
                break;
            case O_NO:
                // Evaluo si esta moviendose hacia derecha o si la velocidad en Y es mayor que
                // delta. Siempre chell debe estar a partir del centro del bloque para inclinarse
                if ((velx > 0 || abs(vely) > DELTA_VEL) && (x() < block->getCenterX()))
                    _tilt = WEST;
                break;
            default:    // Chell no se inclina
                break;
        }
    } else {
        (_tilt != NOT_TILTED) ? (_tilt = NOT_TILTED) : 0;
        if (cname == ROCK) {
            auto rock = (Rock *) other;
            float head_pos = this->y() + _height / 2;
            // Evaluo si esta encima de chell y cayendo
            (rock->y() > head_pos && rock->velocityY() != 0) ? _dead = true : _hit_wall = true;
        } else if (cname == ACID || cname == ENERGY_BALL) {
            _dead = true;
        } else if (cname == ROCK_BLOCK || cname == METAL_BLOCK || cname == GATE || cname == CAKE ||
                   cname == ENERGY_RECEIVER || cname == ENERGY_TRANSMITTER) {
            if (abs(vely) > DELTA_VEL || abs(velx) > DELTA_VEL) {    // Verifico no sea error delta
                _hit_wall = true;
                _move_state = MOVE_STOP;    // Freno cuando colisiona con bloque (saltando o caminando)
            }
            if (cname == CAKE)
                _reached_cake = true;
        } else if (cname == PORTAL) {
            if (_tilt != NOT_TILTED)
                _tilt = NOT_TILTED; // Sale del portal sin inclinacion
            if (!_teleported) {
                auto portal = (Portal *) other;
                if (portal->exitPortal()) {   // Verifico que tenga ambos portales
                    _portal_to_use = portal;    // Asigno portal a atravesar
                    if (_rock_joint) {
                        auto rock = (Rock*) _rock_joint->GetBodyB()->GetUserData();
                        rock->setPortalToUse(portal);  // Teletransporto roca
                    }
                } else {
                    _hit_wall = true;
                }
            }   // Si se teletransporto se ignorara contacto en pre-solve
        }
    }
}

void Chell::endCollitionWith(Collidable *other) {
    auto cname = other->classId();
    if (cname == METAL_DIAGONAL_BLOCK) {
        if (_tilt != NOT_TILTED && (abs(y() - _height / 2 - other->y()) < DELTA_POS))
            _body->SetLinearVelocity({0,0});
        else if (_jump_state == FALLING)
            _body->SetLinearVelocity({_move_force,-_move_force});
        if (abs(y() - _height / 2 - other->y()) < DELTA_POS)   // Chell llego a base de bloque
            _tilt = NOT_TILTED;   // Deja de caminar en diagonal
        else if (x() + width() / 2 < other->x())
            _tilt = NOT_TILTED; // Pase el bloque
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

int Chell::setNewPortal(Portal *portal) {
    int old_portal_id = -1;
    if (portal->colour() == ORANGE_PORTAL) {    // Nuevo portal naranja
        if (_portals.first)
            old_portal_id = _portals.first->id();
        if (_portals.second) {
            portal->setExitPortal(_portals.second);  // Seteo portal de salida
            _portals.second->setExitPortal(portal);
        }
        _portals.first = portal;
    } else {    // Nuevo portal azul
        if (_portals.second)
            old_portal_id = _portals.second->id();
        if (_portals.first) {
            portal->setExitPortal(_portals.first);  // Seteo portal de salida
            _portals.first->setExitPortal(portal);
        }
        _portals.second = portal;
    }
    return old_portal_id;
}

std::pair<int, int> Chell::resetPortals() {
    auto ids = std::make_pair(-1, -1);
    if (_portals.first) {   // Portal naranja
        ids.first = _portals.first->id();
        _portals.first = nullptr;
    }
    if (_portals.second) {  // Portal azul
        ids.second = _portals.second->id();
        _portals.second = nullptr;
    }
    return std::move(ids);
}

int Chell::setNewPinTool(PinTool *pintool) {
    int old_pintool_id = -1;
    if (_pintool)
        old_pintool_id = _pintool->id();
    _pintool = pintool;
    return old_pintool_id;
}

void Chell::resetPinTool() {
    _pintool= nullptr;
}

void Chell::shoot() {
    _shooting = true;
}



void Chell::step(const float &time_step) {
    if (!_dead)
        move();
}

void Chell::liftRock() {
    Rock *rock = nullptr;
    auto velx = _body->GetLinearVelocity().x;
    for (auto it = _body->GetContactList(); it; it = it->next) {
        auto coll1 = (Collidable*) it->contact->GetFixtureB()->GetBody()->GetUserData();
        auto coll2 = (Collidable*) it->contact->GetFixtureA()->GetBody()->GetUserData();
        if (coll1->classId() == ROCK) {
            rock = (Rock *) coll1;
        } else if (coll2->classId() == ROCK) {
            rock = (Rock *) coll2;
        }
        if (rock) {            // Tomo roca segun velocidad
            if ((rock->x() >= x() && velx >= 0) || (rock->x() < x() && velx < 0) ) {
                b2RopeJointDef jointDef;
                jointDef.bodyA = _body;
                jointDef.bodyB = rock->getBody();
                jointDef.collideConnected = false;
                jointDef.maxLength = 0;
                // Creo joint
                _rock_joint = (b2RopeJoint*) _body->GetWorld()->CreateJoint(&jointDef);
                rock->setLifter(this);  // Indico a roca quien lo levanta
                return; // Uni chell a una roca
            }
            rock = nullptr; // Seteo a null roca nuevamente en caso que no se haya podido unir
        }
    }
}

void Chell::dropRock() {
    if (_rock_joint) {
        auto rock = (Rock*) _rock_joint->GetBodyB()->GetUserData();
        rock->removeLifter();
        _body->GetWorld()->DestroyJoint(_rock_joint);
        _rock_joint = nullptr;
    }
}

void Chell::setPortalToUse(Portal *portal) {
    _portal_to_use = portal;
}

