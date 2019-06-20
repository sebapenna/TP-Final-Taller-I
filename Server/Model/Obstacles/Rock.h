#ifndef PORTAL_ROCA_H
#define PORTAL_ROCA_H

#include <Box2D/Box2D.h>
#include <Server/Model/Collidable.h>

class Rock: public Collidable {
private:
    b2Body *_body;
    const size_t _id;
    float _previous_x, _previous_y;
    bool _previously_dead = false;  // Guardo estado previo para identificar cambio
    bool _dead = false;
    const float _width, _height;

public:
    explicit Rock(const size_t &id, b2Body *body, const float& width, const float& height);

    float velocityY();

    b2Body *getBody() const;

    bool isDead() const;

    const size_t id() const;

    void teletransport(float x, float y);

    const uint8_t classId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float x() override;

    const float y() override;

    const float width() override;

    const float height() override;
};


#endif //PORTAL_ROCA_H
