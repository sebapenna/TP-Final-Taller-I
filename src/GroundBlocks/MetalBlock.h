#ifndef TP_FINAL_BLOQUE_METAL_H
#define TP_FINAL_BLOQUE_METAL_H

#include "Block.h"

class MetalBlock: public Block {
public:
    void createPortal(uint8_t ray_orientation) override;
};


#endif //TP_FINAL_BLOQUE_METAL_H
