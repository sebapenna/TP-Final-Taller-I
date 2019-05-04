#include "bloque_metal_diagonal.h"
#include "../exceptions.h"

BloqueMetalDiagonal::BloqueMetalDiagonal(Posicion posicion, uint8_t o)
:Bloque(posicion) {
    _orientacion = o;
}

void BloqueMetalDiagonal::setElemento(ElementoBloque &&n_elem) {
    throw BloqueNoPuedeTenerElementoSobreElException();
}

bool BloqueMetalDiagonal::hasElemento() {
    return false;
}
