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
    const float _width, _height;
    b2Body *_body;

    // Verifica si hay alguna chell debajo de la compuerta, en caso de que este por cerrarse
    void verifyChellsUnderIt();

public:
    explicit Gate(const size_t &id, b2Body *body, const float& width, const float& height);

    ~Gate() override;

    const size_t id() const;

    bool isOpen();

    void addButtonNeeded(Button* button);
    void addEnergyReceiverNeeded(EnergyReceiver* e_receiver);


    void collideWith(Collidable *other) override;
    void endCollitionWith(Collidable *other) override;

    void step(const float &time_step) override;
    bool actedDuringStep() override;

    const uint8_t classId() override;
    const float x() override;
    const float y() override;
    const float width() override;
    const float height() override;
    b2Body *getBody() const override;

    bool isDead(const float &time_step) override;
};


#endif //PORTAL_COMPUERTA_H
