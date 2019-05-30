#ifndef TP_FINAL_BLOQUE_METAL_DIAGONAL_H
#define TP_FINAL_BLOQUE_METAL_DIAGONAL_H

#include <cstdint>
#include "../constants.h"

class MetalDiagonalBlock {
private:
    uint8_t _orientation;   // todo: necesario?

public:
    explicit MetalDiagonalBlock(uint8_t orientation);

    void createPortal(uint8_t ray_orientation);
};


#endif //TP_FINAL_BLOQUE_METAL_DIAGONAL_H
