#include "EnergyBall.h"
#include <Server/Model/constants.h>
#include <Server/Model/GroundBlocks/MetalDiagonalBlock.h>
#include <Server/Model/Obstacles/Gate.h>

EnergyBall::EnergyBall(const size_t &id, b2Body *body, uint8_t direction) : _id(id) {
    _body = body;
    int x_impulse = 0, y_impulse = 0;
    switch (direction) {
        case O_N:
            y_impulse = ENRG_BALL_FORCE;
            break;
        case O_S:
            y_impulse = -1 * ENRG_BALL_FORCE;
            break;
        case O_E:
            x_impulse = ENRG_BALL_FORCE;
            break;
        case O_O:
            x_impulse = -1 * ENRG_BALL_FORCE;
            break;
        default:    // No existe este caso
            break;
    }
    b2Vec2 impulse(x_impulse, y_impulse);
    _body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
    _previous_x = _body->GetPosition().x;
    _previous_y = _body->GetPosition().y;
}

void EnergyBall::updateLifetime() {
    _lifetime += TIME_STEP;
}

bool EnergyBall::isDead() {
    float diff_time = ENERGY_BALL_MAX_LIFETIME - _lifetime;
    return (_dead || diff_time < TIME_STEP);
}

const float EnergyBall::getX() {
    return _body->GetPosition().x;
}

const float EnergyBall::getY() {
    return _body->GetPosition().y;
}

const uint8_t EnergyBall::getClassId() {
    return ENERGY_BALL;
}

b2Body *EnergyBall::getBody() const {
    return _body;
}

size_t EnergyBall::getId() const {
    return _id;
}

void EnergyBall::collideWith(Collidable *other) {
    auto cname = other->getClassId();
    if (cname == ROCK_BLOCK || cname == ACID || cname == BUTTON ||
        cname == ROCK || cname == ENERGY_RECEIVER || cname == CHELL ||
        cname == PIN_TOOL) {
        _dead = true;
    } else if (cname == ENERGY_TRANSMITTER && _lifetime != 0) {
        _dead = true;    // Verifico que no colisiona cuando se crea la bola
    } else if (cname == METAL_BLOCK ||  cname == METAL_DIAGONAL_BLOCK)  {
//        bounce(other);
    } else if (cname == GATE) {
        auto gate = (Gate*) other;
        if (!gate->isOpen())
            _dead = true;
    }
}

void EnergyBall::endCollitionWith(Collidable *other) {

}

bool EnergyBall::actedDuringStep() {
    if (_previously_dead != _dead) {
        _previously_dead = _dead;
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
    return false;
}

//void EnergyBall::bounce(Collidable *other) {
//    auto velx = _body->GetLinearVelocity().x;
//    auto vely = _body->GetLinearVelocity().y;
//    float new_velx, new_vely;
//    if (other->getClassId() == METAL_BLOCK) {   // Rebote en sup. plana es setear velocidad opuesta
//        new_velx = velx * -1;
//        new_vely = vely * -1;
//    } else {    // METAL_DIAGONAL_BLOCK
//        auto block  = (MetalDiagonalBlock*) other;
//        auto orientation  = block->getOrientation();
//        if (velx == 0 && vely < 0) {
//            if (orientation == O_NE || O_NO) {
//                new_vely = 0;
//                (orientation == O_NE) ? (new_velx = -1 * vely) : (new_velx = vely);
//            } else {    // O_SE || O_SO
//                new_velx = 0;
//                new_vely = -1 * vely;
//            }
//        } else if (velx == 0 && vely > 0) {
//            if (orientation == O_SE || O_SO) {
//                new_vely = 0;
//                (orientation == O_SO) ? (new_velx = -1 * vely) : (new_velx = vely);
//            } else {    // O_NE || O_NO
//                new_velx = 0;
//                new_vely = -1 * vely;
//            }
//        } else if (velx > 0 && vely == 0) {
//            if (orientation == O_NO || O_SO) {
//                new_velx = 0;
//                (orientation == O_SO) ? (new_vely = -1 * velx) : (new_vely = velx);
//            } else {    // O_NE || O_SE
//                new_velx = -1 * velx;
//                new_vely = 0;
//            }
//        } else if (velx < 0 && vely == 0) {
//            if (orientation == O_NO || O_SO) {
//                new_velx = 0;
//                (orientation == O_SO) ? (new_vely = -1 * velx) : (new_vely = velx);
//            } else {    // O_NE || O_SE
//                new_velx = -1 * velx;
//                new_vely = 0;
//            }
//        }
//    }
//    _body->SetLinearVelocity({new_velx, new_vely});
//}
