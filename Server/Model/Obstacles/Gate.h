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
    const float _x, _y, _width, _height;

public:
    explicit Gate(const size_t &id, const float& x, const float& y, const float& width,
            const float& height);

    ~Gate() override;

    const size_t id() const;

    bool isOpen();

    void addButtonNeeded(Button* button);

    void addEnergyReceiverNeeded(EnergyReceiver* e_receiver);

    const uint8_t classId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float x() override;

    const float y() override;

    const float width() override;

    const float height() override;

    void step(const float &time_step) override;

    bool isDead(const float &time_step) override;

    b2Body *getBody() const override;
};


#endif //PORTAL_COMPUERTA_H
