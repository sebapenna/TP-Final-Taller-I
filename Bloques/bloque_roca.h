#ifndef TP_FINAL_BLOQUE_ROCA_H
#define TP_FINAL_BLOQUE_ROCA_H

#include "bloque.h"

class BloqueRoca: public Bloque {

public:
    explicit BloqueRoca(Posicion posicion);

    void setElemento(ElementoBloque &&n_elem) override;

    bool hasElemento() override;
};


#endif //TP_FINAL_BLOQUE_ROCA_H
