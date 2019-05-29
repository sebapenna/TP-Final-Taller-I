#ifndef PORTAL_ENERGYRECEIVERDATA_H
#define PORTAL_ENERGYRECEIVERDATA_H


#include <cstdio>

class EnergyReceiverData {
private:
    size_t _id;
    float _x;
    float _y;

public:
    EnergyReceiverData(const size_t& id, const float& x, const float& y);

    size_t getId() const;

    float getX() const;

    float getY() const;
};


#endif //PORTAL_ENERGYRECEIVERDATA_H
