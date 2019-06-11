#ifndef PORTAL_BLOQUE_METAL_DIAGONAL_H
#define PORTAL_BLOQUE_METAL_DIAGONAL_H

#include <cstdint>
#include <Server/Model/Collidable.h>

class MetalDiagonalBlock: public Collidable {
private:
    const float _x;
    const float _y;
    const float _width;
    const float _height;
    const uint8_t _orientation;

public:
    explicit MetalDiagonalBlock(const float& x, const float& y, const float& width, const float&
    height, uint8_t orientation);

    const uint8_t getOrientation() const;

    const uint8_t getClassId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float getX() const;

    const float getY() const;

    const float getWidth() const;

    const float getHeight() const;
};


#endif //PORTAL_BLOQUE_METAL_DIAGONAL_H
