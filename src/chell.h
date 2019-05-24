#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H

#include "Box2D/Box2D.h"

class Chell {
private:
    b2Body *_body;
    const unsigned int _id;
    uint8 _move_state;
    uint8 _jump_state;
    bool _jump;

    // Evita volver a aplicar un impulso en el mismo sentido
    bool movementAlreadyApplied();

    void updateJumpState();

    // Setear argumento en true si se quiere calcular impulso opuesto al actual
    int calculateXImpulse();

public:

    Chell(unsigned int id, b2Body *body);

    const unsigned int getId() const;

    void move_left();

    void move_right();

    void jump();

    void stop_movement();

    void teletransport(float x, float y);

    // Metodo a llamar para que se aplique el movimiento seteado previamente
    void move();

    float getPositionX();

    float getPositionY();
};


#endif //PORTAL_CHELL_H
