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
    const float _x, _y, _width, _height;
    size_t _bodies_on_it = 0;   // Puede que mas de un cuerpo este en contacto con boton

public:
    explicit Button(const size_t &id, const float& x, const float& y, const float& width,
            const float& height);

    ~Button() override;

    void activate();
    void deactivate();
    bool isActivated();

    size_t id() const;

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


#endif //PORTAL_BOTON_H
