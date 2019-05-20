#ifndef TP_FINAL_BLOQUE_ROCA_H
#define TP_FINAL_BLOQUE_ROCA_H

#include "block.h"

class RockBlock: public Block {

public:
    explicit RockBlock(b2Body *body);

    void createPortal(uint8_t ray_orientation) override;
};


#endif //TP_FINAL_BLOQUE_ROCA_H
