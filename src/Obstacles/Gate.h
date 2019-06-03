#ifndef PORTAL_COMPUERTA_H
#define PORTAL_COMPUERTA_H

#include "Button.h"
#include <vector>
#include <src/EnergyBlocks/EnergyReceiver.h>

class Gate: public Collidable {
private:
    bool _open = false;
    std::vector<Button*> _buttons_needed;
    std::vector<EnergyReceiver*>  _energy_reveivers_needed;

public:
    bool isOpen();

    void addButtonNeeded(Button* button);

    void addEnergyReceiverNeeded(EnergyReceiver* e_receiver);

    void updateState();

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;
};


#endif //PORTAL_COMPUERTA_H
