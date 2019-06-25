#include "RockBlockData.h"
#include <Server/Model/World.h>
#include <Server/Model/GroundBlocks/RockBlock.h>

RockBlockData::RockBlockData(const float &width, const float &height,
                             const float &x, const float &y) :
                             _width(width), _height(height), _x(x), _y(y){ }

const float RockBlockData::getWidth() const {
    return _width;
}

const float RockBlockData::getHeight() const {
    return _height;
}

const float RockBlockData::getX() const {
    return _x;
}

const float RockBlockData::getY() const {
    return _y;
}

void RockBlockData::build(World *world, std::shared_ptr<Configuration> config) {
    auto body = BoxCreator::createStaticBox(world->getWorld(), _x, _y, _width / 2, _height / 2);
    auto rock_block = new RockBlock(_x, _y, _width, _height);
    body->SetUserData(rock_block);
    world->addRockBlock(rock_block);
}

