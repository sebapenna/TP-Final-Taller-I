#ifndef PORTAL_CAKE_H
#define PORTAL_CAKE_H

#include "Collidable.h"
#include <Box2D/Box2D.h>


class Cake: public Collidable {
private:
    b2Body *_body;
    size_t _chells_in_contact;  // Contabiliza la cantidad de chells que llegaron a cake

public:
    explicit Cake(b2Body *body);

    const uint8_t getClassId() override;

    float getX();
    float getY();

    size_t getNumberOfChellsInContact() const;

    bool actedDuringStep() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;
};


#endif //PORTAL_CAKE_H
