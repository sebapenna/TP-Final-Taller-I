#include "posicion.h"

Posicion::Posicion(int x, int y) {
    _x = x;
    _y = y;
}

void Posicion::operator=(const Posicion &other) {
    _x = other._x;
    _y = other._y;
}

bool Posicion::igualA(const Posicion &other) {
    return (_x == other._x && _y == other._y);
}

int Posicion::getX() const {
    return _x;
}

int Posicion::getY() const {
    return _y;
}
