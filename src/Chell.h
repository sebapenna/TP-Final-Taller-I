#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H

#include <Box2D/Box2D.h>
#include "Collidable.h"

class Chell: public Collidable {
private:
    b2Body *_body;
    const unsigned int _id;
    uint8 _move_state;
    uint8 _jump_state;
    bool _jump, _dead;

    // Evita volver a aplicar un impulso en el mismo sentido
    bool movementAlreadyApplied();

    void updateJumpState();

    int calculateXImpulse();

public:
    Chell(unsigned int id, b2Body *body);

    float getPositionX();

    float getPositionY();

    b2Body *getBody() const;

    void move_left();

    void move_right();

    void jump();

    void stop_movement();

    void teletransport(float x, float y);

    // Metodo a llamar para que se aplique el movimiento seteado previamente
    void move();

    bool isDead();

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;
};


#endif //PORTAL_CHELL_H
