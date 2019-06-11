#ifndef PORTAL_RECEPTOR_ENERGIA_H
#define PORTAL_RECEPTOR_ENERGIA_H

#include <Server/Model/Collidable.h>
#include <Server/Model/constants.h>

class EnergyReceiver: public Collidable {
private:
    uint8_t _previous_state = NOT_ACTIVATED;    // Estado previo para detectar cambio estado
    uint8_t _state = NOT_ACTIVATED;
    bool _activated = false;
    const size_t _id;
    const float _x, _y;

public:
    explicit EnergyReceiver(const size_t& id, const float& x, const float& y);

    void activate();

    bool isActivated();

    void updateState();

    const size_t getId() const;

    const uint8_t getClassId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float getX() const;

    const float getY() const;
};


#endif //PORTAL_RECEPTOR_ENERGIA_H
