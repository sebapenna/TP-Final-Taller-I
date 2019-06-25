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
    float _previous_x, _previous_y, _move_force, _jump_force;
    b2Body *_body;
    uint8 _move_state;
    uint8 _jump_state, _previous_jump_state;
    int16_t _tilt, _previous_tilt; // Guardo estado previo para identificar cambio
    bool _shooting, _previously_shooting = false;
    bool _teleported = false;
    bool _jump, _dead;
    bool _reached_cake;
    bool _hit_wall;

    // Par de portales: primero sera el naranja y el segundo el azul.
    std::pair<Portal *, Portal *> _portals;
    Portal *_portal_to_use = nullptr; // Portal por el cual teletransportar, podria no ser propio
    PinTool *_pintool = nullptr;

    b2RopeJoint *_rock_joint = nullptr; // Joint vinculando roca que decidio levantar


    // Evita volver a aplicar un impulso en el mismo sentido
    bool movementInXAlreadyApplied();

    // Actualiza jump state
    void updateJumpState();

    // Calcula el impulso a aplicar en eje x en base a move y jump state
    int calculateXImpulse();

    // Metodo a llamar para que se aplique el movimiento seteado previamente
    void move();

    // Setea la nueva posicion e impulso del cuerpo
    void teleport(float x, float y);

public:
    Chell(const size_t &id, b2Body *body, const float &width, const float &height);

    ~Chell() override;

    void setJumpForce(float jumpForce);
    void setMoveForce(float moveForce);

    const float x() override;
    const float y() override;
    const float width() override;
    const float height() override;
    b2Body *getBody() const override ;
    const uint8_t classId() override;
    const size_t id() const;
    bool isDead(const float &time_step) override;
    bool reachedCake();

    // Retorna la orientacion de chell.
    // WEST: inclinado hacia izquierda
    // EAST: inclinado hacia derecha
    // NOT_TILTED: derechp
    int16_t tilt() const;

    // Indica en que direccion se esta moviendo
    // PRE: haber utilizado isMoving para verificar que se este moviendo (por default enviara O_E
    // aunque no se este moviendo)
    uint8_t movementDirection();

    // Ademas de retornar su valor resetea su valor, ya que es accion de un instante
    bool isShooting();
    bool isJumping();
    bool isMoving();
    void move_left();
    void move_right();
    void jump();
    void stopMovement();
    void liftRock();
    void dropRock();
    void shoot();   // Registra que chell realizo un disparo, con o sin creacion de la entidad
    void resetPinTool();    // Borra referencia a pintool actual.
    void kill();     // Mata a la chell, ya sea por suicidio o porque la mataron

    // En caso de que chell ya tuviese un pintool realizará el cambio y retornara el id del viejo
    // (para asi poder ser destruido), de lo contrariores retornara -1
    int setNewPinTool(PinTool *pintool);

    // Asigna nuevo portal a chell. En caso de que chell ya tuviese un portal del mismo color
    // realizará el cambio de portal y retornara el id del viejo (para asi poder ser destruido).
    // Si no tenia un portal del color del nuevo retornara -1. Se encarga de setear el portal de
    // salida al nuevo portal, en caso de que la chell ya tuviese un primer portal.
    int setNewPortal(Portal *portal);

    // Indica que portal atravesara la roca de la joint, por lo tanto chell debe hacer lo mismo
    void setPortalToUse(Portal *portal);

    // Elimina los portales de la chell. En caso de tener previamente portales retornara un par
    // con el id del portal naranja en el primer indice y el azul en el segundo. Si no tuviese
    // alguno o ambos portales retornara -1 en cada posicion.
    std::pair<int, int> resetPortals();

    // Verifica si la chell se teletransporto y en caso de asi ser, setea que ya fue realizado
    bool ifTeleportedSetDone();

    void step(const float &time_step) override;
    void collideWith(Collidable *other) override;
    void endCollitionWith(Collidable *other) override;

    // POST: se debe utilizar el metodo isShooting previo al siguiente step en caso de haber sido
    // true el valor de retorno (independientemente de cual haya sido la fuente de accion) para
    // posiblemente actualizar su valor.
    bool actedDuringStep() override;
};

#endif //PORTAL_CHELL_H
