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

    const uint8_t classId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float x() override;

    const float y() override;

    const float width() override;

    const float height() override;
};


#endif //PORTAL_BLOQUE_ROCA_H
