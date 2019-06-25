#ifndef TP_FINAL_BOLA_ENERGIA_H
#define TP_FINAL_BOLA_ENERGIA_H

#include <cstdint>
#include <Box2D/Box2D.h>
#include <Server/Model/Collidable.h>
#include <Server/Model/Shots/Portal.h>

class EnergyBall: public Collidable {
private:
    b2Body *_body;
    size_t _id;
    float _lifetime = 0, _max_lifetime;
    float _previous_x, _previous_y;
    bool _dead = false;
    const float _radius, _force;
    bool _teleported = false;
    Portal *_portal_to_use = nullptr;

    void teleport(float x, float y);

public:
    EnergyBall(const size_t &id, b2Body *body, uint8_t direction, const float& radius,
            const float &max_lifetime, const float& force);

    ~EnergyBall() override;

    const uint8_t classId() override;
    const float x() override;
    const float y() override;
    // Utilizar a los metodos width y height retornara el diametro de la bola
    const float width() override;
    const float height() override;
    b2Body *getBody() const override;

    size_t id() const;

    bool isDead(const float& time_step) override;


    void collideWith(Collidable *other) override;
    void endCollitionWith(Collidable *other) override;

    void step(const float &time_step) override;
    bool actedDuringStep() override;

    bool ifTeleportedSetDone();
};


#endif //TP_FINAL_BOLA_ENERGIA_H
