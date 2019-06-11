#include <Server/Model/constants.h>
#include <Server/Model/Chell.h>
#include <Server/Model/GroundBlocks/RockBlock.h>
#include <Server/Model/GroundBlocks/MetalBlock.h>
#include <Server/Model/GroundBlocks/MetalDiagonalBlock.h>
#include <Server/Model/EnergyBlocks/EnergyTransmitter.h>
#include <Server/Model/EnergyBlocks/EnergyReceiver.h>
#include <Common/ProtocolTranslator/RockBlockDTO.h>
#include <Common/ProtocolTranslator/MetalBlockDTO.h>
#include <Common/ProtocolTranslator/MetalDiagonalBlockDTO.h>
#include <Common/ProtocolTranslator/EnergyTransmitterDTO.h>
#include <Common/ProtocolTranslator/EnergyReceiverDTO.h>
#include <Server/Model/Obstacles/Acid.h>
#include <Common/ProtocolTranslator/AcidDTO.h>
#include <Common/ProtocolTranslator/ButtonDTO.h>
#include <Server/Model/Obstacles/Button.h>
#include <Server/Model/Obstacles/Gate.h>
#include <Common/ProtocolTranslator/GateDTO.h>
#include <Server/Model/Obstacles/EnergyBarrier.h>
#include <Common/ProtocolTranslator/EnergyBarrierDTO.h>
#include <Server/Model/Obstacles/Rock.h>
#include <Common/ProtocolTranslator/RockDTO.h>
#include <Common/ProtocolTranslator/EnergyBallDTO.h>
#include <Common/ProtocolTranslator/ChellDTO.h>
#include <Common/ProtocolTranslator/ButtonStateDTO.h>
#include <Common/ProtocolTranslator/EnergyTransmitterActivateDTO.h>
#include <Common/ProtocolTranslator/EnergyReceiverActivateDTO.h>
#include <Common/ProtocolTranslator/GateStateDTO.h>
#include <Common/ProtocolTranslator/PortalDTO.h>
#include <Common/ProtocolTranslator/PinToolDTO.h>
#include "WorldObjectDTOTranslator.h"
#include "PositionTranslator.h"

using std::make_shared;

std::shared_ptr<ProtocolDTO> WorldObjectDTOTranslator::translate(Collidable *collidable , bool initial_data) {
    auto cname = collidable->getClassId();
    switch (cname) {
        case ROCK_BLOCK: {
            auto obj = (RockBlock *) collidable;
            auto new_pos = PositionTranslator::translate(cname, obj->getX(), obj->getY(),
                    obj->getWidth(), obj->getHeight());
            return make_shared<RockBlockDTO>(new_pos.first, new_pos.second, obj->getWidth(),
                                             obj->getHeight());
        }
        case METAL_BLOCK: {
            auto obj = (MetalBlock *) collidable;
            auto new_pos = PositionTranslator::translate(cname, obj->getX(), obj->getY(),
                                                         obj->getWidth(), obj->getHeight());
            return make_shared<MetalBlockDTO>(new_pos.first, new_pos.second, obj->getWidth(),
                                             obj->getHeight());
        }
        case METAL_DIAGONAL_BLOCK: {
            auto obj = (MetalDiagonalBlock *) collidable;
            auto new_pos = PositionTranslator::translate(cname, obj->getX(), obj->getY(),
                                                         obj->getWidth(), obj->getHeight());
            // todo: tomo height como largo de cada cara (corregir y agregar width y height a DTO)
            return make_shared<MetalDiagonalBlockDTO>(new_pos.first, new_pos.second,
                    obj->getWidth(), obj->getOrientation());
        }
        case ENERGY_TRANSMITTER: {
            auto obj = (EnergyTransmitter*) collidable;
            if (initial_data) {
                auto new_pos = PositionTranslator::translate(cname, obj->getX(), obj->getY(),
                                                             ENRG_BLOCK_HALF_LEN);
                return make_shared<EnergyTransmitterDTO>(obj->getId(), new_pos.first,
                        new_pos.second, (2 * ENRG_BLOCK_HALF_LEN), obj->getDirection());
            }
            return make_shared<EnergyTransmitterActivateDTO>(obj->getId()); // Se activo

        }
        case ENERGY_RECEIVER: {
            auto obj = (EnergyReceiver*) collidable;
            if (initial_data) {
                auto new_pos = PositionTranslator::translate(cname, obj->getX(), obj->getY(),
                                                             ENRG_BLOCK_HALF_LEN);
                return make_shared<EnergyReceiverDTO>(obj->getId(), new_pos.first, new_pos.second,
                                                      (2 * ENRG_BLOCK_HALF_LEN));
            }
            return make_shared<EnergyReceiverActivateDTO>(obj->getId()); // Se activo

        }
        case ACID: {
            auto obj = (Acid *) collidable;
            auto new_pos = PositionTranslator::translate(cname, obj->getX(), obj->getY(),
                                                         ACID_HALF_WIDTH, ACID_HALF_HEIGHT);
            return make_shared<AcidDTO>(new_pos.first, new_pos.second, (2 * ACID_HALF_WIDTH),
                                        (2 * ACID_HALF_HEIGHT));
        }
        case BUTTON: {
            auto obj = (Button *) collidable;
            if (initial_data) {
                auto new_pos = PositionTranslator::translate(cname, obj->getX(), obj->getY(),
                                                             BUTTON_HALF_WIDTH, BUTTON_HALF_HEIGHT);
                return make_shared<ButtonDTO>(obj->getId(), new_pos.first, new_pos.second,
                        (2 * BUTTON_HALF_WIDTH), (2 * BUTTON_HALF_HEIGHT));
            }
            auto state = NOT_ACTIVATED; // Se registro cambio de estado
            if (obj->isActivated())
                state = ACTIVATED;
            return make_shared<ButtonStateDTO>(obj->getId(), state);
        }
        case GATE: {
            auto obj = (Gate *) collidable;
            if (initial_data) {
                auto new_pos = PositionTranslator::translate(cname, obj->getX(), obj->getY(),
                                                             GATE_HALF_WIDTH, GATE_HALF_HEIGHT);
                return make_shared<GateDTO>(obj->getId(), new_pos.first, new_pos.second,
                                            (2 * GATE_HALF_WIDTH), (2 * GATE_HALF_HEIGHT));
            }
            auto state = CLOSED;
            if (obj->isOpen())
                state = OPEN;
            return make_shared<GateStateDTO>(obj->getId(), state);
        }
        case ENERGY_BARRIER: {
            auto obj = (EnergyBarrier*) collidable;
            auto new_pos = PositionTranslator::translate(cname, obj->getX(), obj->getY(),
                    obj->getWidth() / 2, obj->getHeight() / 2);
            return make_shared<EnergyBarrierDTO>(new_pos.first, new_pos.second, obj->getWidth(),
                    obj->getHeight());
        }
        case ROCK: {
            auto obj = (Rock*) collidable;
            auto new_pos = PositionTranslator::translate(cname, obj->getX(), obj->getY(),
                                                         ROCK_HALF_LEN);
            return make_shared<RockDTO>(obj->getId(), new_pos.first, new_pos.second,
                    2 * ROCK_HALF_LEN, DONT_DELETE);   // Cuerpo no debe ser eliminado
        }
        case ENERGY_BALL: {
            auto obj = (EnergyBall*) collidable;
            auto new_pos = PositionTranslator::translate(cname, obj->getX(), obj->getY(),
                                                         ENRG_BALL_RADIUS);
            return make_shared<EnergyBallDTO>(obj->getId(), new_pos.first, new_pos.second,
                    ENRG_BALL_RADIUS, DONT_DELETE); // Cuerpo no debe ser eliminado
        }
        case CHELL: {
            auto obj = (Chell*) collidable;
            auto new_pos = PositionTranslator::translate(cname, obj->getX(), obj->getY(),
                                                         CHELL_HALF_WIDTH, CHELL_HALF_HEIGHT);
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
            return make_shared<ChellDTO>(obj->getId(), new_pos.first, new_pos.second,
                    (2 * CHELL_HALF_WIDTH), (2 * CHELL_HALF_HEIGHT), obj->movementDirection(),
                    obj->tilt(), moving, jumping, shooting, carring_rock, DONT_DELETE); // No borrar
        }
        case PORTAL: {
            // todo: PORTAL GETTERS
        }
        case PIN_TOOL: {
            // todo: PIN TOOL GETTERS
        }
        default:
            // No existe este caso
            return nullptr;
    }

    // todo: collidabel metodo getX getY /getWidth / getHeight => ENCAPSULO Y ELIMINO REPTEAD NEWPOS
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
            return make_shared<PortalDTO>(object_id, 0, 0, 0, 0, 0, DELETE);
        case PIN_TOOL:
            return make_shared<PinToolDTO>(object_id, 0, 0, 0, 0, DELETE);
        default:    // Comando incorrecto
            return nullptr;
    }
}
