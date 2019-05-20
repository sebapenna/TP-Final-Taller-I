#include <algorithm>

#include "metal_block.h"
#include "src/exceptions.h"

MetalBlock::MetalBlock(b2Body *body) : Block(body) {

}

/* Orientacion del portal sera opuesta a sentido rayo*/
void MetalBlock::createPortal(uint8_t ray_orientation) {
    uint8_t o_portal = 0;
    switch (ray_orientation) {
        case O_N:
            o_portal = O_S;
            break;
        case O_S:
            o_portal = O_N;
            break;
        case O_O:
            o_portal = O_E;
            break;
        case O_E:
            o_portal = O_O;
            break;
        default:
            /* Orientacion del rayo no puede ser otra que las indicadas */
            break;
    }
    /* todo: escenario crear portal*/
//    _portal = new Portal(o_portal);
}

