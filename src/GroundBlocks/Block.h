#ifndef TP_FINAL_BLOQUE_H
#define TP_FINAL_BLOQUE_H

#include "Box2D/Box2D.h"
#include "src/constants.h"

class Block {
protected:

public:
    // Metodo define si el bloque es capaz de establecer un portal
    virtual void createPortal(uint8_t ray_orientation) = 0;
};

#endif //TP_FINAL_BLOQUE_H
