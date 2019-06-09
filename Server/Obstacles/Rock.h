#ifndef PORTAL_ROCA_H
#define PORTAL_ROCA_H

#include <Box2D/Box2D.h>
#include <Server/Collidable.h>

class Rock: public Collidable {
private:
    b2Body *_body;
    float _previous_x, _previous_y;
    bool _previously_dead = false;  // Guardo estado previo para identificar cambio
    bool _dead = false;

public:
    explicit Rock(b2Body *body);

    float getPositionX();

    float getPositionY();

    float getVelocityY();

    b2Body *getBody() const;

    bool isDead() const;

    void teletransport(float x, float y);

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;
};


#endif //PORTAL_ROCA_H
