#include <Server/Model/constants.h>
#include <Server/Model/Chell.h>
#include <Server/Model/GroundBlocks/RockBlock.h>
#include <Server/Model/GroundBlocks/MetalBlock.h>
#include <Server/Model/GroundBlocks/MetalDiagonalBlock.h>
#include <Server/Model/EnergyBlocks/EnergyTransmitter.h>
#include <Server/Model/EnergyBlocks/EnergyReceiver.h>
#include <Common/ProtocolTranslator/DataDTO/RockBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/MetalBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/MetalDiagonalBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyTransmitterDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyReceiverDTO.h>
#include <Server/Model/Obstacles/Acid.h>
#include <Common/ProtocolTranslator/DataDTO/AcidDTO.h>
#include <Common/ProtocolTranslator/DataDTO/ButtonDTO.h>
#include <Server/Model/Obstacles/Button.h>
#include <Server/Model/Obstacles/Gate.h>
#include <Common/ProtocolTranslator/DataDTO/GateDTO.h>
#include <Server/Model/Obstacles/EnergyBarrier.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyBarrierDTO.h>
#include <Server/Model/Obstacles/Rock.h>
#include <Common/ProtocolTranslator/DataDTO/RockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyBallDTO.h>
#include <Common/ProtocolTranslator/DataDTO/ChellDTO.h>
#include <Common/ProtocolTranslator/DataDTO/ButtonStateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyTransmitterActivateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyReceiverActivateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/GateStateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/PortalDTO.h>
#include <Common/ProtocolTranslator/DataDTO/PinToolDTO.h>
#include <Server/Model/Cake.h>
#include <Common/ProtocolTranslator/DataDTO/CakeDTO.h>
#include "WorldObjectDTOTranslator.h"
#include "PositionTranslator.h"

using std::make_shared;

std::shared_ptr<ProtocolDTO> WorldObjectDTOTranslator::translate(Collidable *collidable , bool initial_data) {
    if (!collidable)
        return nullptr;
    auto cname = collidable->classId();
    auto new_pos = PositionTranslator::translate(cname, collidable->x(), collidable->y(),
            collidable->width() / 2, collidable->height() / 2);
    switch (cname) {
        case ROCK_BLOCK: {
            auto obj = (RockBlock *) collidable;
            return make_shared<RockBlockDTO>(new_pos.first, new_pos.second, obj->width(),
                                             obj->height());
        }
        case METAL_BLOCK: {
            auto obj = (MetalBlock *) collidable;
            return make_shared<MetalBlockDTO>(new_pos.first, new_pos.second, obj->width(),
                                             obj->height());
        }
        case METAL_DIAGONAL_BLOCK: {
            auto obj = (MetalDiagonalBlock *) collidable;
            return make_shared<MetalDiagonalBlockDTO>(new_pos.first, new_pos.second,
                    obj->width(), obj->getOrientation());
        }
        case ENERGY_TRANSMITTER: {
            auto obj = (EnergyTransmitter*) collidable;
            if (initial_data) {
                return make_shared<EnergyTransmitterDTO>(obj->id(), new_pos.first,
                        new_pos.second, obj->width(), obj->getDirection());
            }
            return make_shared<EnergyTransmitterActivateDTO>(obj->id()); // Se activo

        }
        case ENERGY_RECEIVER: {
            auto obj = (EnergyReceiver*) collidable;
            if (initial_data) {
                return make_shared<EnergyReceiverDTO>(obj->id(), new_pos.first, new_pos.second,
                                                      obj->width());
            }
            return make_shared<EnergyReceiverActivateDTO>(obj->id()); // Se activo

        }
        case ACID: {
            auto obj = (Acid *) collidable;
            return make_shared<AcidDTO>(new_pos.first, new_pos.second, obj->width(),
                    round(obj->height()));
        }
        case BUTTON: {
            auto obj = (Button *) collidable;
            if (initial_data) {
                return make_shared<ButtonDTO>(obj->id(), new_pos.first, new_pos.second,
                        obj->width(), round(obj->height()));
            }
            auto state = NOT_ACTIVATED; // Se registro cambio de estado
            if (obj->isActivated())
                state = ACTIVATED;
            return make_shared<ButtonStateDTO>(obj->id(), state);
        }
        case GATE: {
            auto obj = (Gate *) collidable;
            if (initial_data) {
                return make_shared<GateDTO>(obj->id(), new_pos.first, new_pos.second,
                                            obj->width(), obj->height());
            }
            auto state = CLOSED;
            if (obj->isOpen())
                state = OPEN;
            return make_shared<GateStateDTO>(obj->id(), state);
        }
        case ENERGY_BARRIER: {
            auto obj = (EnergyBarrier*) collidable;
            return make_shared<EnergyBarrierDTO>(new_pos.first, new_pos.second, obj->width(),
                    obj->height());
        }
        case ROCK: {
            auto obj = (Rock*) collidable;
            return make_shared<RockDTO>(obj->id(), new_pos.first, new_pos.second,
                    obj->width(), DONT_DELETE);   // Cuerpo no debe ser eliminado
        }
        case ENERGY_BALL: {
            auto obj = (EnergyBall*) collidable;
            return make_shared<EnergyBallDTO>(obj->id(), new_pos.first, new_pos.second,
                    obj->width() / 2, DONT_DELETE); // Cuerpo no debe ser eliminado
        }
        case CHELL: {
            auto obj = (Chell*) collidable;
            auto moving = NOT_MOVING;
            if (obj->isMoving())
                moving = MOVING;
            auto jumping = NOT_JUMPING;
            if (obj->isJumping())
                jumping = JUMPING;
            auto shooting = NOT_SHOOTING;
            if (obj->isShooting())
                shooting = SHOOTING;
            auto carring_rock = NOT_CARRYING;
            if (obj->isCarryingRock())
                carring_rock = CARRYING;
            return make_shared<ChellDTO>(obj->id(), new_pos.first, new_pos.second,
                    obj->width(), obj->height(), obj->movementDirection(),
                    obj->tilt(), moving, jumping, shooting, carring_rock, DONT_DELETE); // No borrar
        }
        case CAKE: {
            auto obj = (Cake*) collidable;
            return make_shared<CakeDTO>(new_pos.first, new_pos.second, obj->width());
        }
        case PORTAL: {
            auto obj = (Portal*) collidable;
            return make_shared<PortalDTO>(obj->id(), new_pos.first, new_pos.second,
                    round(obj->width()), round(obj->height()), obj->tilt(), obj->colour(),
                    DONT_DELETE);
        }
        case PIN_TOOL: {
            auto obj = (PinTool*) collidable;
            return make_shared<PinToolDTO>(obj->id(), obj->x(), obj->y(), obj->width(),
                    obj->height(), DONT_DELETE);
        }
        default:
            // No existe este caso
            return nullptr;
    }
}

std::shared_ptr<ProtocolDTO>
WorldObjectDTOTranslator::translate(const size_t &object_id, const uint8_t &object_class_id) {
    // Unicos atributos de importancia seran DELETe y el id
    switch (object_class_id) {
        case ROCK:
            return std::make_shared<RockDTO>(object_id, 0, 0, 0, DELETE);
        case CHELL:
            return make_shared<ChellDTO>(object_id, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, DELETE);
        case ENERGY_BALL:
            return make_shared<EnergyBallDTO>(object_id, 0, 0, 0, DELETE);
        case PORTAL:
            return make_shared<PortalDTO>(object_id, 0, 0, 0, 0, 0, 0, DELETE);
        case PIN_TOOL:
            return make_shared<PinToolDTO>(object_id, 0, 0, 0, 0, DELETE);
        default:    // Comando incorrecto
            return nullptr;
    }
}
