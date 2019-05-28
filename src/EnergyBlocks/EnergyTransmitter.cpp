#include "EnergyTransmitter.h"
#include "src/exceptions.h"

EnergyTransmitter::EnergyTransmitter(b2Body *body, uint8_t direction)
: Block(body) {
    _direction = direction;
}

void EnergyTransmitter::createPortal(uint8_t ray_orientaiton) {
    throw BlockCantCreatePortalException();
}
//
//EnergyBall* EnergyTransmitter::releaseEnergyBall() {
//    /* todo ¿posicion deberia ser la siguiente?*/
//    /* todo: tendria que tener al escenario y que le diga crearBola*/
////    auto *n_bola = new EnergyBall(_posicion, _direction);
////    return std::move(n_bola);
//}
