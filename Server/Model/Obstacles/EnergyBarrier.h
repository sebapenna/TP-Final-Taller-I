#ifndef PORTAL_ENERGYBARRIER_H
#define PORTAL_ENERGYBARRIER_H

#include <Server/Model/Collidable.h>

class EnergyBarrier: public Collidable {
private:
    const float _x, _y, _width, _height;
public:
    EnergyBarrier(const float& x, const float& y, const float& width, const float& height);

    ~EnergyBarrier() override;

    void collideWith(Collidable *other) override;
    void endCollitionWith(Collidable *other) override;

    void step(const float &time_step) override;
    bool actedDuringStep() override;

    const uint8_t classId() override;
    const float x() override;
    const float y() override;
    const float width() override;
    const float height() override;
    b2Body *getBody() const override;

    bool isDead(const float &time_step) override;
};


#endif //PORTAL_ENERGYBARRIER_H
