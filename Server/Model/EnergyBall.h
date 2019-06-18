#ifndef TP_FINAL_BOLA_ENERGIA_H
#define TP_FINAL_BOLA_ENERGIA_H

#include <cstdint>
#include <Box2D/Box2D.h>
#include <Server/Model/Collidable.h>

class EnergyBall: public Collidable {
private:
    b2Body *_body;
    size_t _id;
    float _lifetime = 0;
    float _previous_x, _previous_y;
    bool _dead = false, _previously_dead = false;

public:
    EnergyBall(const size_t &id, b2Body *body, uint8_t direction);

    void updateLifetime();

    bool isDead();

    size_t getId() const;

    b2Body *getBody() const;

    const float getX();

    const float getY();

    const uint8_t getClassId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    void bounce(Collidable *other);
};


#endif //TP_FINAL_BOLA_ENERGIA_H
