#include "RockData.h"
#include <Server/Model/World.h>

RockData::RockData(const float &x, const float &y) : _x(x), _y(y) { }

const float RockData::getX() const {
    return _x;
}

const float RockData::getY() const {
    return _y;
}

void RockData::build(World *world, std::shared_ptr<Configuration> c) {
    auto body = BoxCreator::createDynamicBox(world->getWorld(), _x, _y, c->getRockHalfLen(),
            c->getRockHalfLen(), c->getRockDensity());
    auto *rock = new Rock(world->getNextRockId(), body, c->getRockHalfLen() * 2,
            c->getRockHalfLen() * 2);
    body->SetUserData(rock);
    world->addRock(rock);
}

