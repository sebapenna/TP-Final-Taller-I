#ifndef PORTAL_RECEPTOR_ENERGIA_H
#define PORTAL_RECEPTOR_ENERGIA_H

#include <src/Collidable.h>
#include <src/constants.h>

class EnergyReceiver: Collidable {
private:

    uint8_t _state = NOT_ACTIVATED;
    bool _activated = false;

public:
    void activate();

    bool isActivated();

    void updateState();

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

private:
    void endCollitionWith(Collidable *other) override;
};


#endif //PORTAL_RECEPTOR_ENERGIA_H
