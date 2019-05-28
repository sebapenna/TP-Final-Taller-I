#include "Gate.h"

void Gate::open() {
    _open = true;
}

void Gate::close() {
    _open = false;
}

bool Gate::isOpen() {
    return _open;
}

Gate::Gate() {
    _open = false;
}

Gate &Gate::operator=(Gate &&other) {
    _open = other._open;
    return *this;
}
