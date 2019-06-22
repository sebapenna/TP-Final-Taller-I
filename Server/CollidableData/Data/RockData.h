#ifndef PORTAL_ROCKDATA_H
#define PORTAL_ROCKDATA_H

#include "Server/CollidableData/CollidableData.h"
#include <cstdio>

class RockData : public CollidableData {
private:
    const float _x;
    const float _y;

public:
    RockData(const float& x, const float& y);

    const float getX() const override;

    const float getY() const override;

    void build(World *world, std::shared_ptr<Configuration> config) override;
};


#endif //PORTAL_ROCKDATA_H
