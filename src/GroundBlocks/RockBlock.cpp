#include <algorithm>
#include "RockBlock.h"
#include "src/exceptions.h"

RockBlock::RockBlock(b2Body *body) : Block(body) {

}

void RockBlock::createPortal(uint8_t ray_orientation) {
    throw BlockCantCreatePortalException();
}
