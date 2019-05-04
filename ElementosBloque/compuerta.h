#ifndef TP_FINAL_COMPUERTA_H
#define TP_FINAL_COMPUERTA_H


#include "elemento_bloque.h"
#include "../entidad_sin_movimiento.h"

class Compuerta: public ElementoBloque, EntidadSinMovimiento {
private:
    bool _abierta;

public:
    Compuerta();

    void abrir();

    void cerrar();

    bool estaAbierta();

    Compuerta& operator=(Compuerta &&other);
};


#endif //TP_FINAL_COMPUERTA_H
