#ifndef TP_FINAL_BOTON_H
#define TP_FINAL_BOTON_H


#include "../entidad_sin_movimiento.h"
#include "elemento_bloque.h"

class Boton: public ElementoBloque, EntidadSinMovimiento {
private:
    bool _activado;

public:
    Boton();

    void activar();

    void desactivar();

    bool estaActivado();

    Boton& operator=(Boton &&other);
};


#endif //TP_FINAL_BOTON_H
