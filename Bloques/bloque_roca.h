#ifndef TP_FINAL_BLOQUE_ROCA_H
#define TP_FINAL_BLOQUE_ROCA_H

#include "bloque.h"

class BloqueRoca: public Bloque {

public:
    explicit BloqueRoca(Posicion posicion);

    void crearPortal(uint8_t orientacion_rayo) override;

    void setElemento(ElementoBloque &&n_elem) override;
};


#endif //TP_FINAL_BLOQUE_ROCA_H
