#ifndef TP_FINAL_ENTIDAD_CON_MOVIMIENTO_H
#define TP_FINAL_ENTIDAD_CON_MOVIMIENTO_H


#include "posicion.h"
#include "entidad.h"

class EntidadConMovimiento: public IEntidad {

public:
    void mover(Posicion n_posicion);
};


#endif //TP_FINAL_ENTIDAD_CON_MOVIMIENTO_H
