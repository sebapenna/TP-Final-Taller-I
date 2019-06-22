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
    const float _x, _y, _width, _height;

public:
    explicit EnergyReceiver(const size_t& id, const float& x, const float& y, const float& width,
            const float& height);

    ~EnergyReceiver() override;

    void activate();

    bool isActivated();

    const size_t id() const;

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


#endif //PORTAL_RECEPTOR_ENERGIA_H
