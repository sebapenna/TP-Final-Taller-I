#ifndef PORTAL_METALBLOCKDATA_H
#define PORTAL_METALBLOCKDATA_H


#include "Server/CollidableData/CollidableData.h"

class MetalBlockData : public CollidableData {
private:
    const float _width;
    const float _height;
    const float _x;
    const float _y;

public:
    MetalBlockData(const float& width, const float& height, const float& x,
                  const float& y);

    const float getWidth() const;

    const float getHeight() const;

    const float getX() const override;

    const float getY() const override;

    void build(World *world, std::shared_ptr<Configuration> config) override;
};


#endif //PORTAL_METALBLOCKDATA_H
