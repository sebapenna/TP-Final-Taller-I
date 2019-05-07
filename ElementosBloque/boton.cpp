#include "boton.h"

Boton::Boton(Posicion posicion) {
    _posicion = posicion;
    _activado = false;
}

void Boton::activar() {
    _activado = true;
}

void Boton::desactivar() {
    _activado = false;
}

bool Boton::estaActivado() {
    return _activado;
}

Boton &Boton::operator=(Boton &&other) {
    this->_activado = other._activado;
}
