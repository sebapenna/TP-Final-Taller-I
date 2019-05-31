#ifndef TP_FINAL_BOLA_ENERGIA_H
#define TP_FINAL_BOLA_ENERGIA_H

#include <cstdint>
#include "Box2D/Box2D.h"

class EnergyBall {
private:
    b2Body *_body;
    uint8_t _direction;

public:
    EnergyBall(b2Body *body, uint8_t direction);

    const float getPositionX();

    const float getPositionY();
};


#endif //TP_FINAL_BOLA_ENERGIA_H
