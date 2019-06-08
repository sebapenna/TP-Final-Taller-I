#ifndef TP_FINAL_BOLA_ENERGIA_H
#define TP_FINAL_BOLA_ENERGIA_H

#include <cstdint>
#include <Box2D/Box2D.h>
#include <src/Collidable.h>

class EnergyBall: public Collidable {
private:
    b2Body *_body;
    float _lifetime = 0;
    bool _dead = false;
    bool _kill = false; // Booleano para indicar si es step en que eliminar energy ball

public:
    EnergyBall(b2Body *body, uint8_t direction);

    void updateLifetime();

    bool isDead();

    b2Body *getBody() const;

    const float getPositionX();

    const float getPositionY();

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool kill() const;

    void killed();
};


#endif //TP_FINAL_BOLA_ENERGIA_H
