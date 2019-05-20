#ifndef TP_FINAL_RECEPTOR_ENERGIA_H
#define TP_FINAL_RECEPTOR_ENERGIA_H

#include "src/GroundBlocks/block.h"

class EnergyReceiver: public Block {
private:
    bool _activated;

public:
    void createPortal(uint8_t orientacion_rayo) override;

    void receiveEnergyBall();

    bool isActivated();
};


#endif //TP_FINAL_RECEPTOR_ENERGIA_H
