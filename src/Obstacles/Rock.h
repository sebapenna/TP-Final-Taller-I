#ifndef TP_FINAL_ROCA_H
#define TP_FINAL_ROCA_H

#include "Box2D/Box2D.h"

class Rock {
private:
    b2Body *_body;

public:
    explicit Rock(b2Body *body);

    float getPositionX();

    float getPositionY();

};


#endif //TP_FINAL_ROCA_H
