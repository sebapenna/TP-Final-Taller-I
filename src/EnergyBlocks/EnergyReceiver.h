#ifndef TP_FINAL_RECEPTOR_ENERGIA_H
#define TP_FINAL_RECEPTOR_ENERGIA_H

#include "../constants.h"

class EnergyReceiver {
private:
    uint8_t _state = NOT_ACTIVATED;
    bool _activated = false;

public:
    void createPortal(uint8_t orientacion_rayo);

    void activate();

    bool isActivated();

    void updateState();
};


#endif //TP_FINAL_RECEPTOR_ENERGIA_H
