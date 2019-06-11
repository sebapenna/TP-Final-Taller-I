#ifndef PORTAL_BOTON_H
#define PORTAL_BOTON_H

#include <Server/Model/constants.h>
#include <Server/Model/Collidable.h>

class Button: public Collidable {
private:
    uint8_t _previous_state = NOT_ACTIVATED;    // Estado previo para detectar cambio de estado
    uint8_t _state = NOT_ACTIVATED;
    bool _activated = false;
    size_t _id;
    const float _x, _y;

public:
    explicit Button(const size_t &id, const float& x, const float& y);

    void activate();

    void deactivate();

    bool isActivated();

    size_t getId() const;

    void updateState();

    const uint8_t getClassId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float getX() const;

    const float getY() const;
};


#endif //PORTAL_BOTON_H
