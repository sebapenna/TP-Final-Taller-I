#include "posicion.h"

void Posicion::operator=(const Posicion &other) {
    _x = other._x;
    _y = other._y;
}

bool Posicion::igualA(const Posicion &other) {
    return (_x == other._x && _y == other._y);
}
