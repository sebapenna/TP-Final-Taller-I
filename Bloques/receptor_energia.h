#ifndef TP_FINAL_RECEPTOR_ENERGIA_H
#define TP_FINAL_RECEPTOR_ENERGIA_H


#include "bloque.h"

class ReceptorEnergia: public Bloque {
private:
    bool _activado;

public:
    void setElemento(ElementoBloque &&n_elem) override;

    void crearPortal(uint8_t orientacion_rayo) override;

    void recibirBolaEnergia();

    bool estaActivado();
};


#endif //TP_FINAL_RECEPTOR_ENERGIA_H
