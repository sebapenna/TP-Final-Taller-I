#include "EnergyBarrierData.h"
#include <Server/Model/constants.h>
#include <Server/Model/World.h>
#include <Server/Model/World.h>

EnergyBarrierData::EnergyBarrierData(const float &x, const float &y,
                                     const std::string &o) : _x(x), _y(y) {
    if (o == "V")
        _orientation = O_V;
    else
        _orientation = O_H;
}

const float EnergyBarrierData::getX() const {
    return _x;
}

const float EnergyBarrierData::getY() const {
    return _y;
}

const uint8_t EnergyBarrierData::getOrientation() const {
    return _orientation;
}

void EnergyBarrierData::build(World *world, std::shared_ptr<Configuration> c) {
    float half_height = 0, half_width = 0;
    switch (_orientation) {
        case O_V:
            half_height = c->getBarrierHalfLen();
            half_width = c->getBarrierHalfWidth();
            break;
        case O_H:
            half_height = c->getBarrierHalfWidth();
            half_width = c->getBarrierHalfLen();
            break;
        default:    // No existe este caso
            break;
    }
    auto body = BoxCreator::createStaticBox(world->getWorld(), _x, _y, half_width, half_height);
    auto e_barrier = new EnergyBarrier(_x, _y, 2 * half_width, 2 * half_height);
    body->SetUserData(e_barrier);
    world->addEnergyBarrier(e_barrier);
}
