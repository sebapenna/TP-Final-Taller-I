#ifndef PORTAL_COMPUERTA_H
#define PORTAL_COMPUERTA_H

#include "Button.h"
#include <vector>
#include <Server/Model/EnergyBlocks/EnergyReceiver.h>

class Gate: public Collidable {
private:
    bool _previously_open = false; // Guardo estado previo para identificar cambio
    bool _open = false;
    std::vector<Button*> _buttons_needed;
    std::vector<EnergyReceiver*>  _energy_reveivers_needed;
    const size_t _id;

public:
    explicit Gate(const size_t &id);

    const size_t getId() const;

    bool isOpen();

    void addButtonNeeded(Button* button);

    void addEnergyReceiverNeeded(EnergyReceiver* e_receiver);

    void updateState();

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;
};


#endif //PORTAL_COMPUERTA_H
