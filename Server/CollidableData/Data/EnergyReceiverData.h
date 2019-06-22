#ifndef PORTAL_ENERGYRECEIVERDATA_H
#define PORTAL_ENERGYRECEIVERDATA_H

#include "../CollidableData.h"
#include <cstdio>

class EnergyReceiverData : public CollidableData{
private:
    const size_t _id;
    const float _x;
    const float _y;

public:
    EnergyReceiverData(const size_t& id, const float& x, const float& y);

    const size_t getId() const;

    const float getX() const override;

    const float getY() const override;

    // PRE: Se debe crear en orden de id creciente
    void build(World *world, std::shared_ptr<Configuration> config) override;
};


#endif //PORTAL_ENERGYRECEIVERDATA_H
