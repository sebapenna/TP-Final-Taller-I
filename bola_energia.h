#ifndef TP_FINAL_BOLA_ENERGIA_H
#define TP_FINAL_BOLA_ENERGIA_H

#include <cstdint>
#include "entidad_con_movimiento.h"

class BolaEnergia: EntidadConMovimiento {
private:
    unsigned int _velocidad;
    uint8_t _direccion;

public:
    BolaEnergia(Posicion posicion, uint8_t direccion);
};


#endif //TP_FINAL_BOLA_ENERGIA_H
