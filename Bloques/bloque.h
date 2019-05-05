#ifndef TP_FINAL_BLOQUE_H
#define TP_FINAL_BLOQUE_H

#include "../constantes.h"
#include "../entidad_sin_movimiento.h"
#include "../ElementosBloque/elemento_bloque.h"
#include "../portal.h"

class Bloque: public EntidadSinMovimiento {
protected:
    ElementoBloque *_elemento;
    Portal *_portal;

    explicit Bloque(Posicion posicion);

    ~Bloque();

public:
    virtual void setElemento(ElementoBloque &&n_elem) = 0;

    void removerElemento();

    bool tieneElemento();

    ElementoBloque* getElemento();

    virtual void crearPortal(uint8_t orientacion_rayo) = 0;

    void removerPortal();

};

#endif //TP_FINAL_BLOQUE_H
