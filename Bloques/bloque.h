#ifndef TP_FINAL_BLOQUE_H
#define TP_FINAL_BLOQUE_H

#include "../constantes.h"
#include "../entidad_sin_movimiento.h"
#include "../ElementosBloque/elemento_bloque.h"

class Bloque: public EntidadSinMovimiento {
protected:
    ElementoBloque *_elemento;

    explicit Bloque(Posicion posicion);

public:
    virtual void setElemento(ElementoBloque &&n_elem) = 0;

    void removeElemento();

    virtual bool hasElemento() = 0;

    ElementoBloque* getElemento();

};

#endif //TP_FINAL_BLOQUE_H
