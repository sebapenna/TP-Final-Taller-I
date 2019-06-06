#ifndef PORTAL_ENERGYBARRIERDATA_H
#define PORTAL_ENERGYBARRIERDATA_H

#include <cstdint>
#include <string>

class EnergyBarrierData {
private:
    const float _x;
    const float _y;
    uint8_t _orientation;

public:
    EnergyBarrierData(const float& x, const float& y, const std::string& o);

    const float getX() const;

    const float getY() const;

    const uint8_t getOrientation() const;

};


#endif //PORTAL_ENERGYBARRIERDATA_H
