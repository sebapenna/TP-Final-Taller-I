#include "emisor_energia.h"
#include "../exceptions.h"

EmisorEnergia::EmisorEnergia(Posicion posicion, uint8_t direccion)
: Bloque(posicion) {
    _direccion = direccion;
}

void EmisorEnergia::setElemento(ElementoBloque &&n_elem) {
    throw BloqueNoPuedeTenerElementoSobreElException();
}

void EmisorEnergia::crearPortal(uint8_t orientacion_rayo) {
    throw BloqueNoPermitePortalException();
}

BolaEnergia* EmisorEnergia::emitirBolaEnergia() {
    /* todo ¿posicion deberia ser la siguiente?*/
    auto *n_bola = new BolaEnergia(_posicion, _direccion);
    return std::move(n_bola);
}
