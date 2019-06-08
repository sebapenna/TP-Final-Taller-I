#ifndef PORTAL_ROCA_H
#define PORTAL_ROCA_H

#include <Box2D/Box2D.h>
#include <Server/Collidable.h>

class Rock: public Collidable {
private:
    b2Body *_body;

public:
    explicit Rock(b2Body *body);

    float getPositionX();

    float getPositionY();

    float getVelocityY();

    const std::string getClassName() override;

    void teletransport(float x, float y);

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;
};


#endif //PORTAL_ROCA_H
