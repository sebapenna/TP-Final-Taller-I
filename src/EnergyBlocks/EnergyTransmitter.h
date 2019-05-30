#ifndef TP_FINAL_EMISOR_ENERGIA_H
#define TP_FINAL_EMISOR_ENERGIA_H

#include "src/EnergyBall.h"

class EnergyTransmitter {
private:
    uint8_t _direction; // Direccion en que saldra la Bola Energia

public:
    explicit EnergyTransmitter(uint8_t direction);

    void createPortal(uint8_t ray_orientaiton);

//    EnergyBall* releaseEnergyBall();
};


#endif //TP_FINAL_EMISOR_ENERGIA_H
