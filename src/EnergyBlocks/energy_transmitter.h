#ifndef TP_FINAL_EMISOR_ENERGIA_H
#define TP_FINAL_EMISOR_ENERGIA_H

#include "src/GroundBlocks/block.h"
#include "src/energy_ball.h"

class EnergyTransmitter: public Block {
private:
    uint8_t _direction; // Direccion en que saldra la Bola Energia

public:
    EnergyTransmitter(b2Body *body, uint8_t direction);

    void createPortal(uint8_t ray_orientaiton) override;

//    EnergyBall* releaseEnergyBall();
};


#endif //TP_FINAL_EMISOR_ENERGIA_H
