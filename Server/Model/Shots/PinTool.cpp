#include "PinTool.h"
#include <Server/Model/constants.h>

PinTool::PinTool(const size_t &id, const size_t& chell_id, b2Body *body, const float &width,
        const float &height) : _owner_chell_id(chell_id), _body(body), _width(width),
        _height(height), _id(id) { }

PinTool::~PinTool() = default;

const uint8_t PinTool::classId() {
    return PIN_TOOL;
}

void PinTool::collideWith(Collidable *other) {
    if (other->classId() == PORTAL)
        _dead = true;   // Se creo portal sobre pintool, se la elimina
}

void PinTool::endCollitionWith(Collidable *other) {
    // Colision no tiene efecto sobre el
}

const size_t PinTool::getOwnerChellId() const {
    return _owner_chell_id;
}

const float PinTool::x() {
    return _body->GetPosition().x;
}

const float PinTool::y() {
    return _body->GetPosition().y;
}

const float PinTool::width() {
    return _width;
}

const float PinTool::height() {
    return _height;
}

b2Body *PinTool::getBody() const {
    return _body;
}

const size_t PinTool::id() const {
    return _id;
}

void PinTool::updateLifetime() {
    _lifetime += TIME_STEP;
}

bool PinTool::isDead() {
    float diff_time = PIN_TOOL_LIFETIME - _lifetime;
    return (_dead || diff_time < TIME_STEP);
}

bool PinTool::actedDuringStep() {
    if (_previously_dead != _dead) {
        _previously_dead = _dead;
        return true;
    }
    return false;
}

