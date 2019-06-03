#ifndef PORTAL_BLOQUE_METAL_DIAGONAL_H
#define PORTAL_BLOQUE_METAL_DIAGONAL_H

#include <cstdint>
#include <src/Collidable.h>

class MetalDiagonalBlock: public Collidable {
private:
    uint8_t _orientation;

public:
    explicit MetalDiagonalBlock(uint8_t orientation);

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;
};


#endif //PORTAL_BLOQUE_METAL_DIAGONAL_H
