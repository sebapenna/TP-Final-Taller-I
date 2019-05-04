#include "compuerta.h"

void Compuerta::abrir() {
    _abierta = true;
}

void Compuerta::cerrar() {
    _abierta = false;
}

bool Compuerta::estaAbierta() {
    return _abierta;
}

Compuerta::Compuerta() {
    _abierta = false;
}
