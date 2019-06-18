#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H

#include <Box2D/Box2D.h>
#include "Collidable.h"

class Chell: public Collidable {
private:
    const size_t _id;
    b2Body *_body;
    uint8 _move_state;
    uint8 _jump_state, _previous_jump_state;
    bool _jump, _dead;
    bool _previously_dead = false;
    float _previous_x, _previous_y;
    int16_t _tilt, _previous_tilt; // Guardo estado previo para identificar cambio
    bool _carrying_rock = false, _previously_carrying = false;
    bool _shooting = false;
    bool _hit_wall = false;
    bool _reached_cake = false;

    // Evita volver a aplicar un impulso en el mismo sentido
    bool movementInXAlreadyApplied();

    // Evita volver a aplicar un impulso en el mismo sentido en movimiento diagonal
    bool movementInYAlreadyApplied();

    void updateJumpState();

    int calculateXImpulse();

    // Calcula impulso a aplicar en movimiento diagonal
    int calculateYImpulse();

public:
    Chell(const size_t &id, b2Body *body);

    const size_t getId() const;

    float getX();

    float getY();

    // Indica la orientacion de chell.
    // WEST: inclinado hacia izquierda
    // EAST: inclinado hacia derecha
    // NOT_TILTED: derechp
    int16_t tilt() const;


    b2Body *getBody() const;

    void move_left();

    void move_right();

    void jump();

    // En la simulacion del step el cuerpo avanzara en un primer step por el impulso ya adquirido
    void stopMovement();

    void teletransport(float x, float y);

    // Metodo a llamar para que se aplique el movimiento seteado previamente
    void move();

    bool isDead();

    const uint8_t getClassId() override;

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

    bool isJumping();

    bool isCarryingRock();

    bool isMoving();

    // Indica en que direccion se esta moviendo
    // PRE: haber utilizado isMoving para verificar que se este moviendo (por default enviara O_E
    // aunque no se este moviendo)
    uint8_t movementDirection();

    bool reachedCake();

    // Mata a la chell, ya sea por suicidio o porque todas las otras chell llegaron a cake menos
    // esta y decidieron matarla.
    void kill();
};


#endif //PORTAL_CHELL_H
