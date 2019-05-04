#ifndef TP_FINAL_BOTON_H
#define TP_FINAL_BOTON_H


#include "entidad_sin_movimiento.h"

class Boton: public EntidadSinMovimiento {
private:
    bool _activado;

public:
    Boton();

    void activar();

    void desactivar();

    bool estaActivado();
};


#endif //TP_FINAL_BOTON_H
