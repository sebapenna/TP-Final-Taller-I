#ifndef TP_FINAL_BLOQUE_ROCA_H
#define TP_FINAL_BLOQUE_ROCA_H

#include "Block.h"

class RockBlock: public Block {

public:
    void createPortal(uint8_t ray_orientation) override;
};


#endif //TP_FINAL_BLOQUE_ROCA_H
