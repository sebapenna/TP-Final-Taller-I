#ifndef PORTAL_RECEPTOR_ENERGIA_H
#define PORTAL_RECEPTOR_ENERGIA_H

#include <Server/Collidable.h>
#include <Server/constants.h>

class EnergyReceiver: public Collidable {
private:

    uint8_t _previous_state = NOT_ACTIVATED;    // Estado previo para detectar cambio estado
    uint8_t _state = NOT_ACTIVATED;
    bool _activated = false;

public:
    void activate();

    bool isActivated();

    void updateState();

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;
};


#endif //PORTAL_RECEPTOR_ENERGIA_H
