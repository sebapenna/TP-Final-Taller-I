#ifndef TP_FINAL_EMISOR_ENERGIA_H
#define TP_FINAL_EMISOR_ENERGIA_H

#include "bloque.h"
#include "../bola_energia.h"

class EmisorEnergia: public Bloque {
private:
    uint8_t _direccion;

public:
    EmisorEnergia(Posicion posicion, uint8_t direccion);

    void setElemento(ElementoBloque &&n_elem) override;

    void crearPortal(uint8_t orientacion_rayo) override;

    BolaEnergia* emitirBolaEnergia();
};


#endif //TP_FINAL_EMISOR_ENERGIA_H
