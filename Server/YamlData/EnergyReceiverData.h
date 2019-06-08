#ifndef PORTAL_ENERGYRECEIVERDATA_H
#define PORTAL_ENERGYRECEIVERDATA_H


#include <cstdio>

class EnergyReceiverData {
private:
    const size_t _id;
    const float _x;
    const float _y;

public:
    EnergyReceiverData(const size_t& id, const float& x, const float& y);

    const size_t getId() const;

    const float getX() const;

    const float getY() const;
};


#endif //PORTAL_ENERGYRECEIVERDATA_H
