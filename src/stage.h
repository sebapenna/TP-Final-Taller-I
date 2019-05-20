#ifndef TP_FINAL_ESCENARIO_H
#define TP_FINAL_ESCENARIO_H

#include "Box2D/Box2D.h"

class Stage {
private:
    b2World *_world;

public:
    Stage();

    ~Stage();
};


#endif //TP_FINAL_ESCENARIO_H
