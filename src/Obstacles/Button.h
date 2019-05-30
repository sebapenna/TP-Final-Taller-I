#ifndef TP_FINAL_BOTON_H
#define TP_FINAL_BOTON_H

#include "Box2D/Box2D.h"
#include "../constants.h"

class Button {
private:
    uint8_t _state = NOT_ACTIVATED;
    bool _activated = false;

public:
    void activate();

    void deactivate();

    bool isActivated();

    void updateState();
};


#endif //TP_FINAL_BOTON_H
