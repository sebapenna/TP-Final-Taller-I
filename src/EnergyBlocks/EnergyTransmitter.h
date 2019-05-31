#ifndef TP_FINAL_EMISOR_ENERGIA_H
#define TP_FINAL_EMISOR_ENERGIA_H

#include "src/EnergyBall.h"

class EnergyTransmitter {
private:
    b2Body *_body;
    uint8_t _direction; // Direccion en que saldra la Bola Energia
    float32 _time_elapsed = 0;

public:
    explicit EnergyTransmitter(b2Body *body, uint8_t direction);

    void createPortal(uint8_t ray_orientaiton);

    // Le indica a world si debe crear una EnergyBall
    bool releaseEnergyBall();

    b2Body *getBody() const;

    uint8_t getDirection() const;
};


#endif //TP_FINAL_EMISOR_ENERGIA_H
