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

bool BloqueMetal::hasElemento() {
    return _elemento != nullptr;
}

