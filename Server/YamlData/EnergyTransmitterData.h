#ifndef PORTAL_ENERGYTRANSMITTERDATA_H
#define PORTAL_ENERGYTRANSMITTERDATA_H


class EnergyTransmitterData {
private:
    const float _x;
    const float _y;
    uint8_t _direction;

public:
    EnergyTransmitterData(const float &x, const float &y,
                          const std::string &direction);

    const float getX() const;

    const float getY() const;

    const uint8_t getDirection() const;
};


#endif //PORTAL_ENERGYTRANSMITTERDATA_H
