#ifndef PORTAL_BLOQUE_METAL_H
#define PORTAL_BLOQUE_METAL_H

#include <cstdint>
#include <Server/Model/Collidable.h>

class MetalBlock: public Collidable {
private:
    const float _x;
    const float _y;
    const float _width;
    const float _height;

public:
    MetalBlock(const float& x, const float& y, const float& width, const float& height);

    const uint8_t getClassId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float getX() const;

    const float getY() const;

    const float getWidth() const;

    const float getHeight() const;
};


#endif //PORTAL_BLOQUE_METAL_H
