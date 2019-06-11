#include <Common/ProtocolTranslator/RockBlockDTO.h>
#include <Common/ProtocolTranslator/PlayerChellIdDTO.h>
#include <Common/ProtocolTranslator/RockDTO.h>
#include "DTOProcessor.h"

using std::vector;
using std::shared_ptr;

void DTOProcessor::applyActionToChell(World &world, ProtocolDTO *dto, size_t chell_id) {
    auto chell = world.getChell(chell_id);    // Chell con la que interactuar
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
            chell->stopMovement();
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
            // todo: DROP ROCK
            break;
        case PROTOCOL_QUIT:
            // todo: eliminar chell de WORLD
            break;
        default:    // No existe este caso
            break;
    }
}

std::shared_ptr<ProtocolDTO> DTOProcessor::createDTO(const size_t &player_id) {
    return std::make_shared<PlayerChellIdDTO>(player_id);
}

shared_ptr<ProtocolDTO>DTOProcessor::createDTO(const size_t &object_id,
        const uint8_t &object_class_id) {
    return std::move(WorldObjectDTOTranslator::translate(object_id, object_class_id));
}
