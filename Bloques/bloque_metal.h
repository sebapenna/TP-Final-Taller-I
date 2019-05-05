#ifndef TP_FINAL_BLOQUE_METAL_H
#define TP_FINAL_BLOQUE_METAL_H

#include "bloque.h"

class BloqueMetal: public Bloque {
public:
    explicit BloqueMetal(const Posicion& posicion);

    void crearPortal(uint8_t o_rayo) override;

    void setElemento(ElementoBloque &&n_elem) override;
};


#endif //TP_FINAL_BLOQUE_METAL_H
