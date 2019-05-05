#include "bloque.h"
#include "../exceptions.h"

Bloque::Bloque(Posicion posicion) {
    _posicion = posicion;
    _elemento = nullptr;
    _portal = nullptr;
}

Bloque::~Bloque() {
    delete _portal;
    delete _elemento;
}

ElementoBloque *Bloque::getElemento() {
    return _elemento;
}

void Bloque::removerElemento() {
    delete _elemento;
    _elemento = nullptr;
}

void Bloque::removerPortal() {
    delete _portal;
}

bool Bloque::tieneElemento() {
    return _elemento != nullptr;
}
