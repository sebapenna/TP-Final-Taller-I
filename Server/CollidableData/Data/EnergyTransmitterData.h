#ifndef PORTAL_ENERGYTRANSMITTERDATA_H
#define PORTAL_ENERGYTRANSMITTERDATA_H

#include "Server/CollidableData/CollidableData.h"

class EnergyTransmitterData : public CollidableData {
private:
    const float _x;
    const float _y;
    uint8_t _direction;

public:
    EnergyTransmitterData(const float &x, const float &y,
                          const std::string &direction);

    const float getX() const override;

    const float getY() const override;

    const uint8_t getDirection() const;

    void build(World *world, std::shared_ptr<Configuration> config) override;
};


#endif //PORTAL_ENERGYTRANSMITTERDATA_H
