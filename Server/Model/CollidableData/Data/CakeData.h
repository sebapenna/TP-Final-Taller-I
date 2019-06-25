#ifndef PORTAL_CAKEDATA_H
#define PORTAL_CAKEDATA_H

#include <Server/Model/CollidableData/CollidableData.h>

class CakeData: public CollidableData {
private:
    const float _x;
    const float _y;

public:
    CakeData(const float &x, const float& y);

    const float getX() const override;

    const float getY() const override;

    void build(World *world, std::shared_ptr<Configuration> config) override;

};


#endif //PORTAL_CAKEDATA_H
