#ifndef TP_FINAL_BLOQUE_METAL_DIAGONAL_H
#define TP_FINAL_BLOQUE_METAL_DIAGONAL_H

#include <cstdint>
#include "bloque.h"

class BloqueMetalDiagonal: public Bloque {
private:
    uint8_t _orientacion;

public:
    BloqueMetalDiagonal(Posicion posicion, uint8_t orientacion);

    void setElemento(ElementoBloque &&n_elem) override;

    bool hasElemento() override;
};


#endif //TP_FINAL_BLOQUE_METAL_DIAGONAL_H
