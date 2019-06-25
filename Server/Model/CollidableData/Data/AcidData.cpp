#include <Server/Model/World.h>
#include <Server/Model/Obstacles/Acid.h>
#include "AcidData.h"

AcidData::AcidData(const float &x, const float &y, const float& width) : _x(x), _y(y), _width(width)
{ }

const float AcidData::getX() const {
    return _x;
}

const float AcidData::getY() const {
    return _y;
}

const float AcidData::getWidth() const {
    return _width;
}

void AcidData::build(World *world, std::shared_ptr<Configuration> config) {
    auto body = BoxCreator::createStaticBox(world->getWorld(), _x, _y, _width / 2,
            config->getAcidHalfHeight());
    auto acid = new Acid(_x, _y, _width, config->getAcidHalfHeight() * 2);
    body->SetUserData(acid);
    world->addAcid(acid);
}
