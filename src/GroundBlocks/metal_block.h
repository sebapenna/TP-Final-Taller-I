#ifndef TP_FINAL_BLOQUE_METAL_H
#define TP_FINAL_BLOQUE_METAL_H

#include "block.h"

class MetalBlock: public Block {
public:
    explicit MetalBlock(b2Body *body);

    void createPortal(uint8_t ray_orientation) override;
};


#endif //TP_FINAL_BLOQUE_METAL_H
