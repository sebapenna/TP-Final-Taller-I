#ifndef PORTAL_ENERGYTRANSMITTERDATA_H
#define PORTAL_ENERGYTRANSMITTERDATA_H


class EnergyTransmitterData {
private:
    float _x;
    float _y;
    uint8_t _direction;

public:
    EnergyTransmitterData(const float &x, const float &y,
                          const std::string &direction);

    float getX() const;

    float getY() const;

    uint8_t getDirection() const;
};


#endif //PORTAL_ENERGYTRANSMITTERDATA_H
