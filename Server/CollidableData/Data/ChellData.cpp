#include "ChellData.h"
#include <Server/Model/World.h>

ChellData::ChellData(const size_t &id, const float &x, const float &y) :
_id(id), _x(x), _y(y) { }

const size_t ChellData::getId() const {
    return _id;
}

const float ChellData::getX() const {
    return _x;
}

const float ChellData::getY() const {
    return _y;
}

void ChellData::build(World *world, std::shared_ptr<Configuration> c) {
    auto body = BoxCreator::createDynamicBox(world->getWorld(), _x, _y, c->getChellHalfWidth(),
            c->getChellHalfHeight(), c->getChellDensity());
    auto chell = new Chell(world->getNextChellId(), body, c->getChellHalfWidth() * 2,
            c->getChellHalfHeight() * 2);
    chell->setJumpForce(c->getJumpForce());
    chell->setMoveForce(c->getMoveForce());
    body->SetUserData(chell);
    body->SetGravityScale(c->getChellGravityScale());
    world->addChell(chell);
}
