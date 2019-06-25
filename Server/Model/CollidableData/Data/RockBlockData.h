#ifndef PORTAL_ROCKBLOCKDATA_H
#define PORTAL_ROCKBLOCKDATA_H

#include "Server/Model/CollidableData/CollidableData.h"

class RockBlockData : public CollidableData {
private:
    const float _width;
    const float _height;
    const float _x;
    const float _y;

public:
    RockBlockData(const float& width, const float& height, const float& x,
            const float& y);

    const float getWidth() const;

    const float getHeight() const;

    const float getX() const override;

    const float getY() const override;

    void build(World *world, std::shared_ptr<Configuration> config) override;
};


#endif //PORTAL_ROCKBLOCKDATA_H
