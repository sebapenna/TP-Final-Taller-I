#ifndef PORTAL_ENERGYTRANSMITTERDATA_H
#define PORTAL_ENERGYTRANSMITTERDATA_H


class EnergyTransmitterData {
private:
    float _x;
    float _y;

public:
    EnergyTransmitterData(const float& x, const float& y);

    float getX() const;

    float getY() const;
};


#endif //PORTAL_ENERGYTRANSMITTERDATA_H
