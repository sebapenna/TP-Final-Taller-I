#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H

#include <Box2D/Box2D.h>
#include "Collidable.h"

class Chell: public Collidable {
private:
    const unsigned int _id;
    b2Body *_body;
    uint8 _move_state;
    uint8 _jump_state;
    bool _jump, _dead;
    bool _previously_dead = false;
    float _previous_x, _previous_y;
    int16_t _tilt, _previous_tilt; // Guardo estado previo para identificar cambio
    bool _carrying_rock = false, _previously_carrying = false;
    bool _shooting = false;

    // Evita volver a aplicar un impulso en el mismo sentido
    bool movementAlreadyApplied();

    void updateJumpState();

    int calculateXImpulse();

public:
    Chell(unsigned int id, b2Body *body);

    const unsigned int getId() const;

    float getPositionX();

    float getPositionY();

    int16_t tilt() const;

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

    // POST: se debe utilizar el metodo isShooting previo al siguiente step en caso de haber sido
    // true el valor de retorno (independientemente de cual haya sido la fuente de accion) para
    // posiblemente actualizar su valor.
    bool actedDuringStep() override;

    // Ademas de retornar su valor resetea su valor, ya que se trata de una accion que no
    // perdura en el tiempo.
    bool isShooting();
    // todo: buscar alternativa a como esta hecho shooting
};


#endif //PORTAL_CHELL_H
