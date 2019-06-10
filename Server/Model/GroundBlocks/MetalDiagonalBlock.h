#ifndef PORTAL_BLOQUE_METAL_DIAGONAL_H
#define PORTAL_BLOQUE_METAL_DIAGONAL_H

#include <cstdint>
#include <Server/Model/Collidable.h>

class MetalDiagonalBlock: public Collidable {
private:
    const uint8_t _orientation;

public:
    explicit MetalDiagonalBlock(uint8_t orientation);

    const uint8_t getOrientation() const;

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;
};


#endif //PORTAL_BLOQUE_METAL_DIAGONAL_H
