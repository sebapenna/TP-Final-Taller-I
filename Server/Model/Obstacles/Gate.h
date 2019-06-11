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
    const float _x, _y;

public:
    explicit Gate(const size_t &id, const float& x, const float& y);

    const size_t getId() const;

    bool isOpen();

    void addButtonNeeded(Button* button);

    void addEnergyReceiverNeeded(EnergyReceiver* e_receiver);

    void updateState();

    const uint8_t getClassId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float getX() const;

    const float getY() const;
};


#endif //PORTAL_COMPUERTA_H
