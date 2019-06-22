#ifndef TP_FINAL_BOLA_ENERGIA_H
#define TP_FINAL_BOLA_ENERGIA_H

#include <cstdint>
#include <Box2D/Box2D.h>
#include <Server/Model/Collidable.h>

class EnergyBall: public Collidable {
private:
    b2Body *_body;
    size_t _id;
    float _lifetime = 0, _max_lifetime, _time_step;
    float _previous_x, _previous_y;
    bool _dead = false;
    const float _radius;

public:
    EnergyBall(const size_t &id, b2Body *body, uint8_t direction, const float& radius,
            const float &max_lifetime, const float &time_step);

    ~EnergyBall() override;

    void updateLifetime();

    bool isDead();

    size_t id() const;

    b2Body *getBody() const;

    const uint8_t classId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float x() override;

    const float y() override;

    // Utilizar a los metodos width y height retornara el diametro de la bola
    const float width() override;
    const float height() override;
};


#endif //TP_FINAL_BOLA_ENERGIA_H
