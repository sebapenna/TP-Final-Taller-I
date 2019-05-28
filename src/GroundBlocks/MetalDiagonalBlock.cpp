#include "MetalDiagonalBlock.h"
#include "src/exceptions.h"

MetalDiagonalBlock::MetalDiagonalBlock(b2Body *body, uint8_t orientation)
:Block(body) {
    _orientation = orientation;
}

void MetalDiagonalBlock::createPortal(uint8_t ray_orientation) {
    uint8_t o_portal = 0;
    switch (_orientation) {
        case O_NE:
            if (ray_orientation == O_S || ray_orientation == O_O) /* Cara diagonal */
                o_portal = _orientation;
            else (ray_orientation == O_N) ? (o_portal = O_S) : (o_portal = O_O);
            break;
        case O_NO:
            if (ray_orientation == O_S || ray_orientation == O_E) /* Cara diagonal */
                o_portal = _orientation;
            else (ray_orientation == O_N) ? (o_portal = O_S) : (o_portal = O_E);
            break;
        case O_SO:
            if (ray_orientation == O_N || ray_orientation == O_E) /* Cara diagonal */
                o_portal = _orientation;
            else (ray_orientation == O_S) ? (o_portal = O_N) : (o_portal = O_E);
            break;
        case O_SE:
            if (ray_orientation == O_N || ray_orientation == O_O) /* Cara diagonal */
                o_portal = _orientation;
            else (ray_orientation == O_S) ? (o_portal = O_N) : (o_portal = O_O);
            break;
    }
    /* todo: escenario crear portal*/
//    _portal = new Portal(o_portal);
}
