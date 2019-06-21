#include <algorithm>

#include "MetalBlock.h"
#include <Server/Model/constants.h>

using std::abs;

const uint8_t MetalBlock::classId() {
    return METAL_BLOCK;
}

void MetalBlock::collideWith(Collidable *other) {
    // No realiza ninguna accion
}

void MetalBlock::endCollitionWith(Collidable *other) {
    // No realiza ninguna accion
}

bool MetalBlock::actedDuringStep() {
    return false;   // Nunca realiza accion durante un step
}

MetalBlock::MetalBlock(const float &x, const float &y, const float &width, const float &height) :
_x(x), _y(y), _width(width), _height(height) { }

const float MetalBlock::x() {
    return _x;
}

const float MetalBlock::y() {
    return _y;
}

const float MetalBlock::width() {
    return _width;
}

const float MetalBlock::height() {
    return _height;
}

float MetalBlock::getSubBlockCenterX(const float& x) {
    auto distance = abs(abs(_x) - abs(x));
    if (distance <= BLOCK_DIVISION / 2)
        return _x;
    int factor = 1; // x > _x
    if (x < _x)
        factor = -1;
    float origin = _x + factor * ((_width - BLOCK_DIVISION) / 2);   // Borde bloque (izq/der)
    while (true) {
        distance = abs(abs(origin) - abs(x));
        if (distance <= float(BLOCK_DIVISION) / 2)
            return origin;
        origin -= (factor * BLOCK_DIVISION/2);    // Muevo en un bloque
    }
}

float MetalBlock::getSubBlockCenterY(const float &y) {
    auto distance = abs(abs(_y) - abs(y));
    if (distance <= BLOCK_DIVISION / 2)
        return _y;
    int factor = 1; // y > _y
    if (y < _y)
        factor = -1;
    float origin = _y + factor * ((_height - BLOCK_DIVISION) / 2);   // Borde bloque (arriba/abajo)
    while (true) {
        distance = abs(abs(origin) - abs(y));
        if (distance <= BLOCK_DIVISION / 2)
            return origin;
        origin -= (factor * BLOCK_DIVISION);    // Muevo en un bloque
    }
}

MetalBlock::~MetalBlock() = default;
