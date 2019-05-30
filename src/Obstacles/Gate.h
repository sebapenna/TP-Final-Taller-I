#ifndef TP_FINAL_COMPUERTA_H
#define TP_FINAL_COMPUERTA_H

#include "../EnergyBlocks/EnergyReceiver.h"
#include "Button.h"
#include <vector>

class Gate {
private:
    bool _open = false;
    std::vector<Button*> _buttons_needed;
    std::vector<EnergyReceiver*>  _energy_reveivers_needed;

public:
    bool isOpen();

    void addButtonNeeded(Button* button);

    void addEnergyReceiverNeeded(EnergyReceiver* e_receiver);

    void updateState();
};


#endif //TP_FINAL_COMPUERTA_H
