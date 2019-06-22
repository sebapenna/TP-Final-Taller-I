#ifndef PORTAL_COLLIDABLE_H
#define PORTAL_COLLIDABLE_H

#include <string>
#include <Box2D/Box2D.h>

class Collidable {
public:
    virtual ~Collidable() = default;

    virtual const uint8_t classId() = 0;

    virtual void step(const float &time_step) = 0;

    // Indica si durante el step el objeto realizo alguna accion
    virtual bool actedDuringStep() = 0;

    virtual void collideWith(Collidable *other) = 0;

    virtual void endCollitionWith(Collidable *other) = 0;

    virtual bool isDead(const float &time_step) = 0;

    virtual b2Body* getBody() const = 0;

    virtual const float x() = 0;
    virtual const float y() = 0;
    virtual const float width() = 0;
    virtual const float height() = 0;
};

#endif //PORTAL_COLLIDABLE_H
