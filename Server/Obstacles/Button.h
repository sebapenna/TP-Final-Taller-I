#ifndef PORTAL_BOTON_H
#define PORTAL_BOTON_H

#include <Server/constants.h>
#include <Server/Collidable.h>

class Button: public Collidable {
private:
    uint8_t _previous_state = NOT_ACTIVATED;    // Estado previo para detectar cambio de estado
    uint8_t _state = NOT_ACTIVATED;
    bool _activated = false;

public:
    void activate();

    void deactivate();

    bool isActivated();

    void updateState();

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;
};


#endif //PORTAL_BOTON_H
