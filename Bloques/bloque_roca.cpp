#include <algorithm>
#include "bloque_roca.h"
#include "../exceptions.h"

BloqueRoca::BloqueRoca(Posicion posicion) : Bloque(posicion) {

}

void BloqueRoca::setElemento(ElementoBloque &&n_elem) {
    if (_elemento)
        throw BloqueOcupadoException();
    _elemento = std::move(&n_elem);
}

bool BloqueRoca::hasElemento() {
    return _elemento != nullptr;
}
