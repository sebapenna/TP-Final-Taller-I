#ifndef TP_FINAL_BLOQUE_METAL_DIAGONAL_H
#define TP_FINAL_BLOQUE_METAL_DIAGONAL_H

#include <cstdint>
#include "Block.h"

class MetalDiagonalBlock: public Block {
private:
    uint8_t _orientation;   // todo: necesario?

public:
    MetalDiagonalBlock(b2Body *body, uint8_t orientation);

    void createPortal(uint8_t ray_orientation) override;
};


#endif //TP_FINAL_BLOQUE_METAL_DIAGONAL_H
