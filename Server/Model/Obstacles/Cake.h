#ifndef PORTAL_CAKE_H
#define PORTAL_CAKE_H

#include "Server/Model/Collidable.h"
#include <Box2D/Box2D.h>


class Cake: public Collidable {
private:
    b2Body *_body;
    size_t _chells_in_contact;  // Contabiliza la cantidad de chells que llegaron a cake
    const float _width, _height;

public:
    explicit Cake(b2Body *body, const float& width, const float& height);

    ~Cake() override;

    void step(const float &time_step) override;
    bool actedDuringStep() override;

    void collideWith(Collidable *other) override;
    void endCollitionWith(Collidable *other) override;

    const uint8_t classId() override;
    const float x() override;
    const float y() override;
    const float width() override;
    const float height() override;
    b2Body *getBody() const override;

    bool isDead(const float &time_step) override;

    size_t getChellsInContact() const;
};


#endif //PORTAL_CAKE_H
