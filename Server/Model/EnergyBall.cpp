#include "EnergyBall.h"
#include <Server/Model/constants.h>
#include <Server/Model/GroundBlocks/MetalDiagonalBlock.h>
#include <Server/Model/Obstacles/Gate.h>

EnergyBall::EnergyBall(const size_t &id, b2Body *body, uint8_t direction, const float& radius,
        const float &max_lifetime, const float &force) : _id(id),
        _max_lifetime(max_lifetime), _radius(radius), _force(force) {
    _body = body;
    int x_impulse = 0, y_impulse = 0;
    switch (direction) {
        case O_N:
            y_impulse = _force;
            break;
        case O_S:
            y_impulse = -1 * _force;
            break;
        case O_E:
            x_impulse = _force;
            break;
        case O_O:
            x_impulse = -1 * _force;
            break;
        default:    // No existe este caso
            break;
    }
    b2Vec2 impulse(x_impulse, y_impulse);
    _body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
    _previous_x = _body->GetPosition().x;
    _previous_y = _body->GetPosition().y;
}

EnergyBall::~EnergyBall()  = default;

bool EnergyBall::isDead(const float& time_step) {
    float diff_time = _max_lifetime - _lifetime;
    return (_dead || diff_time < time_step);
}

const uint8_t EnergyBall::classId() {
    return ENERGY_BALL;
}

b2Body *EnergyBall::getBody() const {
    return _body;
}

size_t EnergyBall::id() const {
    return _id;
}
const float EnergyBall::x() {
    return _body->GetPosition().x;
}

const float EnergyBall::y() {
    return _body->GetPosition().y;
}

const float EnergyBall::width() {
    return _radius * 2;
}

const float EnergyBall::height() {
    return _radius * 2;
}

void EnergyBall::collideWith(Collidable *other) {
    auto cname = other->classId();
    if (cname == ROCK_BLOCK || cname == ACID || cname == BUTTON ||
        cname == ROCK || cname == ENERGY_RECEIVER || cname == CHELL ||
        cname == PIN_TOOL) {
        _dead = true;
    } else if (cname == ENERGY_TRANSMITTER && _lifetime != 0) {
        _dead = true;    // Verifico que no colisiona cuando se crea la bola
    } else if (cname == GATE) {
        auto gate = (Gate*) other;
        if (!gate->isOpen())
            _dead = true;
    } else if (cname == PORTAL) {
        if (!_teleported) {
            auto portal = (Portal *) other;
            if (portal->exitPortal())   // Verifico que tenga ambos portales
                _portal_to_use = portal;    // Asigno portal a atravesar
        }   // Si se teletransporto se ignorara contacto en pre-solve
    }
}

void EnergyBall::endCollitionWith(Collidable *other) { }

bool EnergyBall::actedDuringStep() {
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

void EnergyBall::teleport(float x, float y) {
    // todo: calculo velocidad al salir
    float impulse_x = _force * _portal_to_use->exitPortal()->normal().x;

    float impulse_y =  _force * _portal_to_use->exitPortal()->normal().y;
    b2Vec2 new_pos(x,y);
    _body->SetTransform(new_pos, 0);
    _body->SetLinearVelocity({0,0});    // Anulo velocidad que tenia
    _body->ApplyLinearImpulse({impulse_x, impulse_y}, _body->GetWorldCenter(), true);
}

void EnergyBall::step(const float &time_step) {
    _lifetime += time_step;
    if (_portal_to_use) {   // Bola se debe teletransportar
        float newx = _portal_to_use->exitPortal()->x();
        float newy = _portal_to_use->exitPortal()->y();
        teleport(newx, newy);
        _portal_to_use = nullptr;   // Teletransportacion realizada
        _teleported = true; // Indico que bola se teletransporto durante step
    }
}

bool EnergyBall::ifTeleportedSetDone() {
    if (_teleported) {
        _teleported = false;    // Bola ya realizo teletransportacion
        return true;
    }
    return false;
}


