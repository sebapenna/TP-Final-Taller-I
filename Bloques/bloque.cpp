#include "bloque.h"

Bloque::Bloque(Posicion posicion) {
    _posicion = posicion;
    _elemento = nullptr;
}

ElementoBloque *Bloque::getElemento() {
    return _elemento;
}

void Bloque::removeElemento() {
    delete _elemento;
    _elemento = nullptr;
}
