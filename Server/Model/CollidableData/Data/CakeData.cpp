#include "CakeData.h"
#include <Server/Model/World.h>
#include <Server/Configuration.h>

CakeData::CakeData(const float &x, const float &y) : _x(x), _y(y) { }

const float CakeData::getX() const {
    return _x;
}

const float CakeData::getY() const {
    return _y;
}

void CakeData::build(World *world, std::shared_ptr<Configuration> c) {
    auto body = BoxCreator::createStaticBox(world->getWorld(), _x, _y, c->getCakeHalfLen(),
            c->getCakeHalfLen());
    auto cake = new Cake(body, c->getCakeHalfLen() * 2, c->getCakeHalfLen() * 2);
    body->SetUserData(cake);
    world->addCake(cake);
}
