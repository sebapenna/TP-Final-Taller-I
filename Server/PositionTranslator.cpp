#include "PositionTranslator.h"
#include <Server/Model/constants.h>

using std::pair;
using std::make_pair;

pair<int16_t, int16_t> PositionTranslator::translate(const int16_t &class_id, const float &x,
        const float &y, const float &half_width, const float &half_height) {
    if (class_id == METAL_DIAGONAL_BLOCK || class_id == ENERGY_BALL)
        return std::move(make_pair(x, y));  // No se modifica la posicion
    int16_t new_x = x - half_width;
    int16_t new_y = y - half_height;
    return std::move(make_pair(new_x, new_y));
}

std::pair<int16_t, int16_t>
PositionTranslator::translate(const int16_t &class_id, const float &x, const float &y,
                              const float &half_length) {
    return std::move(translate(class_id, x, y, half_length, half_length));
}
