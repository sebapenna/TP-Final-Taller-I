#include "bloque_metal_diagonal.h"
#include "../exceptions.h"

BloqueMetalDiagonal::BloqueMetalDiagonal(Posicion posicion, uint8_t o)
:Bloque(posicion) {
    _orientacion = o;
}

void BloqueMetalDiagonal::setElemento(ElementoBloque &&n_elem) {
    if (_elemento)
        throw BloqueOcupadoException();
    _elemento = std::move(&n_elem);
}

void BloqueMetalDiagonal::crearPortal(uint8_t o_rayo) {
    delete _portal;
    uint8_t o_portal = 0;
    switch (_orientacion) {
        case O_NE:
            if (o_rayo == O_S || o_rayo == O_O) /* Cara diagonal */
                o_portal = _orientacion;
            else (o_rayo == O_N) ? (o_portal = O_S) : (o_portal = O_O);
            break;
        case O_NO:
            if (o_rayo == O_S || o_rayo == O_E) /* Cara diagonal */
                o_portal = _orientacion;
            else (o_rayo == O_N) ? (o_portal = O_S) : (o_portal = O_E);
            break;
        case O_SO:
            if (o_rayo == O_N || o_rayo == O_E) /* Cara diagonal */
                o_portal = _orientacion;
            else (o_rayo == O_S) ? (o_portal = O_N) : (o_portal = O_E);
            break;
        case O_SE:
            if (o_rayo == O_N || o_rayo == O_O) /* Cara diagonal */
                o_portal = _orientacion;
            else (o_rayo == O_S) ? (o_portal = O_N) : (o_portal = O_O);
            break;
    }
    _portal = new Portal(o_portal);
}
