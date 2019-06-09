#include "DTOProcessor.h"

DTOProcessor::DTOProcessor(World *world) : _world(world ) { }

void DTOProcessor::applyActionToChell(ProtocolDTO *dto, size_t chell_id) {
    auto chell = _world->getChell(chell_id);    // Chell con la que interactuar
    switch (dto->getClassId()) {
        case PROTOCOL_MOVE_LEFT:
            chell->move_left();
            break;
        case PROTOCOL_MOVE_RIGHT:
            chell->move_right();
            break;
        case PROTOCOL_JUMP:
            chell->jump();
            break;
        case PROTOCOL_STOP:
            chell->stop_movement();
            break;
        case PROTOCOL_SHOOT_PORTAL:
            // todo: DISPARAR PORTAL
            break;
        case PROTOCOL_SHOOT_PIN_TOOL:
            // todo: DISPARAR PIN TOOL
            break;
        case PROTOCOL_LIFT_ROCK:
            // todo: LIFT ROCK
            break;
        case PROTOCOL_DROP_ROCK:
            // todo: DROP ROCL
            break;
        default:    // No existe este caso
            break;
    }
}
