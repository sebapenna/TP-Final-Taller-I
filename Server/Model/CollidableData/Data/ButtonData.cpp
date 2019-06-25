#include <cstdio>
#include <Server/Configuration.h>
#include <Server/Model/Obstacles/Button.h>
#include <Server/Model/World.h>
#include "ButtonData.h"

ButtonData::ButtonData(const size_t &id, const float &x, const float &y) :
_id(id), _x(x), _y(y) { }

const size_t ButtonData::getId() const {
    return _id;
}

const float ButtonData::getX() const {
    return _x;
}

const float ButtonData::getY() const {
    return _y;
}

void ButtonData::build(World *world, std::shared_ptr<Configuration> config) {
    auto body = BoxCreator::createStaticBox(world->getWorld(), _x, _y, config->getButtonHalfWidth(),
            config->getButtonHalfHeight());
    auto *button = new Button(world->getNextButtonId(), _x, _y, config->getButtonHalfWidth() * 2,
            config->getButtonHalfHeight() * 2);
    body->SetUserData(button);
    world->addButton(button);
}
