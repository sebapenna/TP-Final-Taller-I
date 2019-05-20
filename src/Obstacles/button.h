#ifndef TP_FINAL_BOTON_H
#define TP_FINAL_BOTON_H

#include "obstacle.h"

class Button: public Obstacle {
private:
    bool _activated;

public:
    Button(b2Body *body);

    void activate();

    void deactivate();

    bool isActivated();

    Button& operator=(Button &&other);
};


#endif //TP_FINAL_BOTON_H
