#ifndef PORTAL_ENERGYBARRIERDATA_H
#define PORTAL_ENERGYBARRIERDATA_H

#include <cstdint>
#include <string>
#include "../CollidableData.h"

class EnergyBarrierData: public CollidableData {
private:
    const float _x;
    const float _y;
    uint8_t _orientation;

public:
    EnergyBarrierData(const float& x, const float& y, const std::string& o);

    const float getX() const override;

    const float getY() const override;

    const uint8_t getOrientation() const;

    void build(World *world, std::shared_ptr<Configuration> config) override;
};


#endif //PORTAL_ENERGYBARRIERDATA_H
