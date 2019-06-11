#ifndef PORTAL_POSITIONTRANSLATOR_H
#define PORTAL_POSITIONTRANSLATOR_H

#include <iostream>
#include <cstdint>

// Convierte la posicion del modelo a la posicion a enviar a traves del protocolo, es decir, la
// posicion de la punta inferior izquierda del bloque. En caso de cuerpo ser una bola de energia
// se envia posicion del centro (width y height no tienen relevancia)
struct PositionTranslator {
    // half_width y half_height deben ser ancho y alto de medio cuerpo
    // Se retorna par<x, y>
    static std::pair<int16_t, int16_t> translate(const int16_t& class_id, const float& x,
            const float& y, const float& half_width, const float& half_height);

    // Mismo traductor pero para objetos cuadrados
    static std::pair<int16_t, int16_t> translate(const int16_t& class_id, const float& x,
            const float& y, const float& half_length);
};


#endif //PORTAL_POSITIONTRANSLATOR_H
