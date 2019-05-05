#include "bola_energia.h"
#include "constantes.h"

BolaEnergia::BolaEnergia(Posicion posicion, uint8_t direccion) {
    _posicion = posicion;
    _direccion = direccion;
    _velocidad = VELOCIDAD;
}
