#include "MetalBlockData.h"
#include <Server/Model/World.h>

MetalBlockData::MetalBlockData(const float &width, const float &height,
                               const float &x, const float &y) :
                               _width(width), _height(height), _x(x), _y(y) { }

const float MetalBlockData::getWidth() const {
    return _width;
}

const float MetalBlockData::getHeight() const {
    return _height;
}

const float MetalBlockData::getX() const {
    return _x;
}

const float MetalBlockData::getY() const {
    return _y;
}

void MetalBlockData::build(World *world, std::shared_ptr<Configuration> config) {
    auto body = BoxCreator::createStaticBox(world->getWorld(), _x, _y, _width / 2, _height / 2);
    auto metal_block = new MetalBlock(_x, _y, _width, _height);
    body->SetUserData(metal_block);
    world->addMetalBlock(metal_block);
}

