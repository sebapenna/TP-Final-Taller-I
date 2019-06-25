#ifndef PORTAL_ACIDDATA_H
#define PORTAL_ACIDDATA_H

#include <Server/Model/CollidableData/CollidableData.h>

class AcidData: public CollidableData {
private:
    const float _x;
    const float _y;
    const float _width;

public:
    AcidData(const float& x, const float& y, const float& width);

    const float getX() const override;

    const float getY() const override;

    const float getWidth() const;

    void build(World *world, std::shared_ptr<Configuration> config) override;
};


#endif //PORTAL_ACIDDATA_H
