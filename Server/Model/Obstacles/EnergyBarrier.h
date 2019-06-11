#ifndef PORTAL_ENERGYBARRIER_H
#define PORTAL_ENERGYBARRIER_H

#include <Server/Model/Collidable.h>

class EnergyBarrier: public Collidable {
private:
    const float _x, _y, _width, _height;
public:
    EnergyBarrier(const float& x, const float& y, const float& width, const float& height);

    const uint8_t getClassId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float getX() const;

    const float getY() const;

    const float getWidth() const;

    const float getHeight() const;
};


#endif //PORTAL_ENERGYBARRIER_H
