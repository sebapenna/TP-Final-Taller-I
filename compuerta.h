#ifndef TP_FINAL_COMPUERTA_H
#define TP_FINAL_COMPUERTA_H


#include "elemento_bloque.h"

class Compuerta: public ElementoBloque {
private:
    bool _abierta;

public:
    Compuerta();

    void abrir();

    void cerrar();

    bool estaAbierta();
};


#endif //TP_FINAL_COMPUERTA_H
