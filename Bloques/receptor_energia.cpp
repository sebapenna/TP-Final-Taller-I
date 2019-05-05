#include "receptor_energia.h"
#include "../exceptions.h"

void ReceptorEnergia::setElemento(ElementoBloque &&n_elem) {
    throw BloqueNoPuedeTenerElementoSobreElException();
}

void ReceptorEnergia::crearPortal(uint8_t orientacion_rayo) {
    throw BloqueNoPermitePortalException();
}

void ReceptorEnergia::recibirBolaEnergia() {
    _activado = true;
}

bool ReceptorEnergia::estaActivado() {
    return _activado;
}
