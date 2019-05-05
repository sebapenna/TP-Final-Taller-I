#include <algorithm>

#include "bloque_metal.h"
#include "../exceptions.h"

BloqueMetal::BloqueMetal(const Posicion& posicion) : Bloque(posicion) {
}

void BloqueMetal::setElemento(ElementoBloque &&n_elem) {
    if (_elemento)
        throw BloqueOcupadoException();
    _elemento = std::move(&n_elem);
}

/* Orientacion del portal sera opuesta a sentido rayo*/
void BloqueMetal::crearPortal(uint8_t o_rayo) {
    delete _portal;
    uint8_t o_portal = 0;
    switch (o_rayo) {
        case O_N:
            o_portal = O_S;
            break;
        case O_S:
            o_portal = O_N;
            break;
        case O_O:
            o_portal = O_E;
            break;
        case O_E:
            o_portal = O_O;
            break;
        default:
            /* Orientacion del rayo no puede ser otra que las indicadas */
            break;
    }
    _portal = new Portal(o_portal);
}

