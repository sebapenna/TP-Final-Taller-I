#ifndef PORTAL_BLOQUE_ROCA_H
#define PORTAL_BLOQUE_ROCA_H

#include <cstdint>
#include <Server/Model/Collidable.h>

class RockBlock: public Collidable {
private:
    const float _x;
    const float _y;
    const float _width;
    const float _height;

public:
    RockBlock(const float& x, const float& y, const float& width, const float& height);

    ~RockBlock() override;

    void collideWith(Collidable *other) override;
    void endCollitionWith(Collidable *other) override;

    void step(const float &time_step) override;
    bool actedDuringStep() override;

    const uint8_t classId() override;
    const float x() override;
    const float y() override;
    const float width() override;
    const float height() override;
    b2Body *getBody() const override;

    bool isDead(const float &time_step) override;
};


#endif //PORTAL_BLOQUE_ROCA_H
