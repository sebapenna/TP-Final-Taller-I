#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H

#include <Box2D/Box2D.h>
#include "Collidable.h"
#include "Server/Model/Shots/Portal.h"
#include "Server/Model/Shots/PinTool.h"

class Chell: public Collidable {
private:
    const size_t _id;
    const float _width, _height;
    b2Body *_body;
    uint8 _move_state;
    uint8 _jump_state, _previous_jump_state;
    bool _jump, _dead;
    float _previous_x, _previous_y;
    int16_t _tilt, _previous_tilt; // Guardo estado previo para identificar cambio
    bool _shooting, _previously_shooting = false;
    bool _hit_wall;
    bool _reached_cake;
    bool _teleported = false;
    // Par de portales: primero sera el naranja y el segundo el azul.
    std::pair<Portal *, Portal *> _portals;
    Portal *_portal_to_use = nullptr; // Portal por el cual teletransportar, podria no ser propio
    PinTool *_pintool = nullptr;

    b2RopeJoint *_rock_joint = nullptr;

    float _move_force;
    float _jump_force;

    // Evita volver a aplicar un impulso en el mismo sentido
    bool movementInXAlreadyApplied();

    void updateJumpState();

    int calculateXImpulse();

public:
    Chell(const size_t &id, b2Body *body, const float &width, const float &height);

    ~Chell() override;

    const size_t id() const;

    // Indica la orientacion de chell.
    // WEST: inclinado hacia izquierda
    // EAST: inclinado hacia derecha
    // NOT_TILTED: derechp
    int16_t tilt() const;


    b2Body *getBody() const override;

    void move_left();

    void move_right();

    void jump();

    // En la simulacion del step el cuerpo avanzara en un primer step por el impulso ya adquirido
    void stopMovement();

    void teleport(float x, float y);

    bool ifTeleportedSetDone();

    // Metodo a llamar para que se aplique el movimiento seteado previamente
    void move();

    bool isDead(const float& time_step) override;

    const uint8_t classId() override;

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

    bool isMoving();

    // Indica en que direccion se esta moviendo
    // PRE: haber utilizado isMoving para verificar que se este moviendo (por default enviara O_E
    // aunque no se este moviendo)
    uint8_t movementDirection();

    bool reachedCake();

    // Mata a la chell, ya sea por suicidio o porque todas las otras chell llegaron a cake menos
    // esta y decidieron matarla.
    void kill();

    // Asigna nuevo portal a chell. En caso de que chell ya tuviese un portal del mismo color
    // realizará el cambio de portal y retornara el id del viejo (para asi poder ser destruido).
    // Si no tenia un portal del color del nuevo retornara -1. Se encarga de setear el portal de
    // salida al nuevo portal, en caso de que la chell ya tuviese un primer portal.
    int setNewPortal(Portal *portal);

    int setNewPinTool(PinTool *pintool);

    // Elimina los portales de la chell. En caso de tener previamente portales retornara un par
    // con el id del portal naranja en el primer indice y el azul en el segundo. Si no tuviese
    // alguno o ambos portales retornara -1 en cada posicion.
    std::pair<size_t, size_t> resetPortals();

    // Borra referencia a pintool actual.
    void resetPinTool();

    // Registra que chell realizo un disparo, independientemente si crea o no portal o pintool
    void shoot();

    const float x() override;

    const float y() override;

    const float width() override;

    const float height() override;

    void setJumpForce(float jumpForce);

    void setMoveForce(float moveForce);

    void step(const float &time_step) override;

    void liftRock();

    void dropRock();

    // Indica que portal atravesara la roca, por lo tanto chell debe hacer lo mismo
    void setPortalToUse(Portal *portal);
};


#endif //PORTAL_CHELL_H
