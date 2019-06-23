#include <Common/ProtocolTranslator/DataDTO/RockBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/PlayerChellIdDTO.h>
#include <Common/ProtocolTranslator/DataDTO/RockDTO.h>
#include <Common/ProtocolTranslator/GameStateDTO/BeginDTO.h>
#include <Common/exceptions.h>
#include <Common/ProtocolTranslator/DataDTO/CakeDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/ShootPortalDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/ShootPinToolDTO.h>
#include "DTOProcessor.h"

using std::vector;
using std::shared_ptr;

void DTOProcessor::applyActionToChell(World *world, ProtocolDTO *dto, size_t chell_id) {
    auto chell = world->getChell(chell_id);    // Chell con la que interactuar
    if (!chell) // Chell no se encuentra en el mapa
        return;
    switch (dto->getClassId()) {
        case PROTOCOL_MOVE_LEFT:
            chell->move_left();
            break;
        case PROTOCOL_MOVE_RIGHT:
            chell->move_right();
            break;
        case PROTOCOL_JUMP:
            try {
                chell->jump();
            } catch(ChellNotOnGroundException& e) { } // Ignoro exception
            break;
        case PROTOCOL_STOP:
            chell->stopMovement();
            break;
        case PROTOCOL_COMMIT_SUICIDE:
            chell->kill();
            break;
        case PROTOCOL_KILL_MISSING_CHELL:
            world->killLastingChell(chell_id);
            break;
        case PROTOCOL_SHOOT_PORTAL: {
            auto p_dto = (ShootPortalDTO *) dto;
            world->shootPortal(chell_id, p_dto->getX(), p_dto->getY(), p_dto->getColor());
            break;
        } case PROTOCOL_RESET_PORTALS:
            world->resetPortals(chell_id);
            break;
        case PROTOCOL_SHOOT_PIN_TOOL: {
            auto p_dto = (ShootPinToolDTO *) dto;
            world->shootPinTool(chell_id, p_dto->getX(), p_dto->getY());
            break;
        } case PROTOCOL_LIFT_ROCK:
            chell->liftRock();
            break;
        case PROTOCOL_DROP_ROCK:
            chell->dropRock();
            break;
        case PROTOCOL_QUIT:
            chell->kill();  // Mato chell de jugador que se fue
            break;
        default:    // No existe este caso
            break;
    }
}

std::shared_ptr<ProtocolDTO> DTOProcessor::createPlayerIdDTO(const size_t &player_id) {
    return std::make_shared<PlayerChellIdDTO>(player_id);
}

shared_ptr<ProtocolDTO>DTOProcessor::createDeletedDTO(const size_t &object_id,
                                                      const uint8_t &object_class_id) {
    return std::move(WorldObjectDTOTranslator::translate(object_id, object_class_id));
}

std::shared_ptr<ProtocolDTO> DTOProcessor::createBeginDTO() {
    return std::make_shared<BeginDTO>();
}

void DTOProcessor::createDTO(Collidable *collidable, vector<shared_ptr<ProtocolDTO>> &output,
        bool initial_data) {
    output.push_back(std::move(WorldObjectDTOTranslator::translate(collidable, initial_data)));
}
