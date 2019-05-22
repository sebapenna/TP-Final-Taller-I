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

    bool forceAlreadyApplied();

    uint8 lastMovement();

public:

    Chell(unsigned int id, b2Body *body);

    const unsigned int getId() const;

    void move_left();

    void move_right();

    void jump();

    void stop_movement();

    void teletransport(float x, float y);

    void move();

    float getX();

    float getY();

    void updateJumpState();
};


#endif //PORTAL_CHELL_H
