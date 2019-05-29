#ifndef PORTAL_ENERGYBARRIERDATA_H
#define PORTAL_ENERGYBARRIERDATA_H

#include <cstdint>
#include <string>

class EnergyBarrierData {
private:
    float _x;
    float _y;
    uint8_t _orientation;

public:
    EnergyBarrierData(const float& x, const float& y, const std::string& o);

    float getX() const;

    float getY() const;

    uint8_t getOrientation() const;

};


#endif //PORTAL_ENERGYBARRIERDATA_H
