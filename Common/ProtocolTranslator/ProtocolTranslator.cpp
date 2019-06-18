#include <Common/ProtocolTranslator/protocol_macros.h>
#include "ProtocolTranslator.h"
#include "Common/ProtocolTranslator/PlayerActionsDTO/ShootPortalDTO.h"
#include "Common/ProtocolTranslator/PlayerActionsDTO/ShootPinToolDTO.h"
#include "Common/ProtocolTranslator/PlayerActionsDTO/LiftRockDTO.h"
#include "Common/ProtocolTranslator/PlayerActionsDTO/MoveLeftDTO.h"
#include "Common/ProtocolTranslator/PlayerActionsDTO/MoveRightDTO.h"
#include "Common/ProtocolTranslator/PlayerActionsDTO/StopDTO.h"
#include "Common/ProtocolTranslator/PlayerActionsDTO/JumpDTO.h"
#include "Common/ProtocolTranslator/PlayerActionsDTO/DropRockDTO.h"
#include "Common/ProtocolTranslator/DataDTO/PlayerChellIdDTO.h"
#include "Common/ProtocolTranslator/DataDTO/RockBlockDTO.h"
#include "Common/ProtocolTranslator/DataDTO/MetalBlockDTO.h"
#include "Common/ProtocolTranslator/DataDTO/MetalDiagonalBlockDTO.h"
#include "Common/ProtocolTranslator/DataDTO/EnergyTransmitterDTO.h"
#include "Common/ProtocolTranslator/DataDTO/EnergyReceiverDTO.h"
#include "Common/ProtocolTranslator/DataDTO/AcidDTO.h"
#include "Common/ProtocolTranslator/DataDTO/ButtonDTO.h"
#include "Common/ProtocolTranslator/DataDTO/GateDTO.h"
#include "Common/ProtocolTranslator/DataDTO/EnergyBarrierDTO.h"
#include "Common/ProtocolTranslator/DataDTO/RockDTO.h"
#include "Common/ProtocolTranslator/DataDTO/EnergyBallDTO.h"
#include "Common/ProtocolTranslator/DataDTO/PortalDTO.h"
#include "Common/ProtocolTranslator/DataDTO/PinToolDTO.h"
#include "Common/ProtocolTranslator/DataDTO/ChellDTO.h"
#include "Common/ProtocolTranslator/DataDTO/ButtonStateDTO.h"
#include "Common/ProtocolTranslator/DataDTO/EnergyTransmitterActivateDTO.h"
#include "Common/ProtocolTranslator/DataDTO/EnergyReceiverActivateDTO.h"
#include "Common/ProtocolTranslator/DataDTO/GateStateDTO.h"
#include "Common/ProtocolTranslator/GameStateDTO/QuitDTO.h"
#include "Common/ProtocolTranslator/GameStateDTO/BeginDTO.h"
#include "Common/ProtocolTranslator/DataDTO/CakeDTO.h"
#include <vector>
#include <iostream>
#include <Common/ProtocolTranslator/PlayerActionsDTO/CommitSuicideDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/KillMissingChellDTO.h>

using std::vector;
using std::move;
using std::shared_ptr;
using std::make_shared;

/********************* DTO a Vector ************************/
int ProtocolTranslator::translate(const ProtocolDTO *dto, vector<int16_t> &output) {
    output.push_back(dto->getClassId());    // Siempre primer valor es el ID
    switch (dto->getClassId()) {
        case PROTOCOL_BEGIN:
            output.push_back(BEGIN_ARGS);
            break;

        case PROTOCOL_QUIT:
            output.push_back(QUIT_ARGS);
            break;

        case PROTOCOL_KILL_MISSING_CHELL:
            output.push_back(KILL_MISSING_CHELL_ARGS);
            break;

        case PROTOCOL_COMMIT_SUICIDE:
            output.push_back(COMMIT_SUICIDE_ARGS);
            break;

        case PROTOCOL_MOVE_LEFT:
            output.push_back(MOVE_LEFT_ARGS);
            break;  // No tiene mas datos a agregar

        case PROTOCOL_MOVE_RIGHT:
            output.push_back(MOVE_RIGHT_ARGS);
            break;  // No tiene mas datos a agregar

        case PROTOCOL_JUMP:
            output.push_back(JUMP_ARGS);
            break;  // No tiene mas datos a agregar

        case PROTOCOL_STOP:
            output.push_back(STOP_ARGS);
            break;  // No tiene mas datos a agregar

        case PROTOCOL_SHOOT_PORTAL:
            output.push_back(SHOOT_PORTAL_ARGS);
            shootPortal(dto, output);
            break;

        case PROTOCOL_SHOOT_PIN_TOOL:
            output.push_back(SHOOT_PT_ARGS);
            shootPinTool(dto, output);
            break;

        case PROTOCOL_LIFT_ROCK:
            output.push_back(LIFT_ROCK_ARGS);
            liftRock(dto, output);
            break;

        case PROTOCOL_DROP_ROCK:
            output.push_back(DROP_ROCK_ARGS);
            break;  // No tiene mas datos a agregar

        case PROTOCOL_PLAYER_CHELL_ID:
            output.push_back(PLAYER_CHELL_ID_ARGS);
            playerChellId(dto, output);
            break;

        case PROTOCOL_ROCK_BLOCK_DATA:
            output.push_back(ROCK_BLOCK_ARGS);
            rockBlockData(dto, output);
            break;

        case PROTOCOL_METAL_BLOCK_DATA:
            output.push_back(METAL_BLOCK_ARGS);
            metalBlockData(dto, output);
            break;

        case PROTOCOL_METAL_DIAGONAL_BLOCK_DATA:
            output.push_back(METAL_DIAG_BLOCK_ARGS);
            metalDiagonalBlockData(dto, output);
            break;

        case PROTOCOL_ENERGY_TRANSMITTER_DATA:
            output.push_back(ENRG_TRANSM_ARGS);
            energyTransmitterData(dto, output);
            break;

        case PROTOCOL_ENERGY_RECEIVER_DATA:
            output.push_back(ENRG_RECVR_ARGS);
            energyReceiverData(dto, output);
            break;

        case PROTOCOL_ACID_DATA:
            output.push_back(ACID_ARGS);
            acidData(dto ,output);
            break;

        case PROTOCOL_BUTTON_DATA:
            output.push_back(BUTTON_ARGS);
            buttonData(dto, output);
            break;

        case PROTOCOL_GATE_DATA:
            output.push_back(GATE_ARGS);
            gateData(dto, output);
            break;

        case PROTOCOL_ENERGY_BARRIER_DATA:
            output.push_back(ENRG_BARRIER_ARGS);
            energyBarrierData(dto, output);
            break;

        case PROTOCOL_ROCK_DATA:
            output.push_back(ROCK_ARGS);
            rockData(dto, output);
            break;

        case PROTOCOL_ENERGY_BALL_DATA:
            output.push_back(ENRG_BALL_ARGS);
            energyBallData(dto, output);
            break;

        case PROTOCOL_PORTAL_DATA:
            output.push_back(PORTAL_ARGS);
            portalData(dto, output);
            break;

        case PROTOCOL_PIN_TOOL_DATA:
            output.push_back(PIN_TOOL_ARGS);
            pinToolData(dto, output);
            break;

        case PROTOCOL_CHELL_DATA:
            output.push_back(CHELL_ARGS);
            chellData(dto ,output);
            break;

        case PROTOCOL_CAKE_DATA:
            output.push_back(CAKE_ARGS);
            cakeData(dto, output);
            break;

        case PROTOCOL_BUTTON_CHANGE_STATE:
            output.push_back(BUTTON_CHANGE_ARGS);
            buttonState(dto, output);
            break;

        case PROTOCOL_ENERGY_TRANSMITTER_ACTIVATE:
            output.push_back(ENRG_TRANSM_ACTV_ARGS);
            energyTransmitterActivate(dto, output);
            break;

        case PROTOCOL_ENERGY_RECEIVER_ACTIVATE:
            output.push_back(ENRG_RECVR_ACTV_ARGS);
            energyReceiverActivate(dto, output);
            break;

        case PROTOCOL_GATE_CHANGE_STATE:
            output.push_back(GATE_CHANGE_ARGS);
            gateState(dto, output);
            break;

        default:    // Comando no existente en el protocolo
            output.clear(); // Elimino ID incorrecto
            return -1;
    }
    return output.size();
}

/********************* Vector a DTO ************************/
shared_ptr<ProtocolDTO> ProtocolTranslator::translate(const vector<int16_t> &input) {
    int command = input.at(0);
    switch (command) {
        case PROTOCOL_BEGIN:
            return make_shared<BeginDTO>();

        case PROTOCOL_QUIT:
            return make_shared<QuitDTO>();

        case PROTOCOL_COMMIT_SUICIDE:
            return make_shared<CommitSuicideDTO>();
            
        case PROTOCOL_KILL_MISSING_CHELL:
            return make_shared<KillMissingChellDTO>();

        case PROTOCOL_MOVE_LEFT:
            return make_shared<MoveLeftDTO>();

        case PROTOCOL_MOVE_RIGHT:
            return make_shared<MoveRightDTO>();

        case PROTOCOL_JUMP:
            return make_shared<JumpDTO>();

        case PROTOCOL_STOP:
            return make_shared<StopDTO>();

        case PROTOCOL_SHOOT_PORTAL:
            return make_shared<ShootPortalDTO>(input[SHOOT_PORTAL_COLOUR_POS],
                    input[SHOOT_PORTAL_X_POS], input[SHOOT_PORTAL_Y_POS]);

        case PROTOCOL_SHOOT_PIN_TOOL:
            return make_shared<ShootPinToolDTO>(input[SHOOT_PT_X_POS], input[SHOOT_PT_Y_POS]);

        case PROTOCOL_LIFT_ROCK:
            return make_shared<LiftRockDTO>(input[LIFT_ROCK_ID_POS]);

        case PROTOCOL_DROP_ROCK:
            return make_shared<DropRockDTO>();

        case PROTOCOL_PLAYER_CHELL_ID:
            return make_shared<PlayerChellIdDTO>(input[PLAYER_CHELL_ID_POS]);

        case PROTOCOL_ROCK_BLOCK_DATA:
            return make_shared<RockBlockDTO>(input[ROCK_BLOCK_X_POS], input[ROCK_BLOCK_Y_POS],
                    input[ROCK_BLOCK_WIDTH_POS], input[ROCK_BLOCK_HEIGHT_POS]);

        case PROTOCOL_METAL_BLOCK_DATA:
            return make_shared<MetalBlockDTO>(input[METAL_BLOCK_X_POS], input[METAL_BLOCK_Y_POS],
                    input[METAL_BLOCK_WIDTH_POS], input[METAL_BLOCK_HEIGHT_POS]);

        case PROTOCOL_METAL_DIAGONAL_BLOCK_DATA:
            return make_shared<MetalDiagonalBlockDTO>(input[METAL_DIAG_BLOCK_X_POS],
                    input[METAL_DIAG_BLOCK_Y_POS], input[METAL_DIAG_BLOCK_SIDE_LEN_POS],
                    input[METAL_DIAG_BLOCK_ORIENT_POS]);
        case PROTOCOL_ENERGY_TRANSMITTER_DATA:

            return make_shared<EnergyTransmitterDTO>(input[ENRG_TRANSM_ID_POS],
                    input[ENRG_TRANSM_X_POS], input[ENRG_TRANSM_Y_POS],
                    input[ENRG_TRANSM_SIDE_LEN_POS], input[ENRG_TRANSM_DIRECTION_POS]);
        case PROTOCOL_ENERGY_RECEIVER_DATA:

            return make_shared<EnergyReceiverDTO>(input[ENRG_RECVR_ID_POS], input[ENRG_RECVR_X_POS],
                    input[ENRG_RECVR_Y_POS], input[ENRG_RECVR_SIDE_LEN_POS]);
        case PROTOCOL_ACID_DATA:

            return make_shared<AcidDTO>(input[ACID_X_POS], input[ACID_Y_POS], input[ACID_WIDTH_POS],
                    input[ACID_HEIGHT_POS]);
        case PROTOCOL_BUTTON_DATA:

            return make_shared<ButtonDTO>(input[BUTTON_ID_POS], input[BUTTON_X_POS],
                    input[BUTTON_Y_POS], input[BUTTON_WIDTH_POS], input[BUTTON_HEIGHT_POS]);
        case PROTOCOL_GATE_DATA:

            return make_shared<GateDTO>(input[GATE_ID_POS], input[GATE_X_POS],
                    input[GATE_Y_POS], input[GATE_WIDTH_POS], input[GATE_HEIGHT_POS]);

        case PROTOCOL_ENERGY_BARRIER_DATA:
            return make_shared<EnergyBarrierDTO>(input[ENRG_BARRIER_X_POS],
                    input[ENRG_BARRIER_Y_POS], input[ENRG_BARRIER_WIDTH_POS],
                    input[ENRG_BARRIER_HEIGHT_POS]);

        case PROTOCOL_ROCK_DATA:
            return make_shared<RockDTO>(input[ROCK_ID_POS], input[ROCK_X_POS], input[ROCK_Y_POS],
                               input[ROCK_SIDE_LEN_POS], input[ROCK_DELETE_STATE_POS]);

        case PROTOCOL_ENERGY_BALL_DATA:
            return make_shared<EnergyBallDTO>(input[ENRG_BALL_ID_POS], input[ENRG_BALL_X_POS],
                    input[ENRG_BALL_Y_POS], input[ENRG_BALL_RADIUS_POS],
                    input[ENRG_BALL_DELETE_STATE_POS]);

        case PROTOCOL_PORTAL_DATA:
            return make_shared<PortalDTO>(input[PORTAL_ID_POS], input[PORTAL_X_POS],
                    input[PORTAL_Y_POS], input[PORTAL_WIDTH_POS], input[PORTAL_HEIGHT_POS],
                    input[PORTAL_COLOUR_POS], input[PORTAL_DELETE_STATE_POS]);

        case PROTOCOL_PIN_TOOL_DATA:
            return make_shared<PinToolDTO>(input[PIN_TOOL_ID_POS], input[PIN_TOOL_X_POS],
                    input[PIN_TOOL_Y_POS], input[PIN_TOOL_WIDTH_POS], input[PIN_TOOL_HEIGHT_POS],
                    input[PIN_TOOL_DELETE_STATE_POS]);

        case PROTOCOL_CHELL_DATA:
            return make_shared<ChellDTO>(input[CHELL_ID_POS], input[CHELL_X_POS],
                    input[CHELL_Y_POS], input[CHELL_WIDTH_POS], input[CHELL_HEIGHT_POS],
                    input[CHELL_DIRECTION_POS], input[CHELL_TILTED_POS], input[CHELL_MOVING_POS],
                    input[CHELL_JUMPING_POS], input[CHELL_SHOOTING_POS],
                    input[CHELL_CARRYING_ROCK_POS], input[CHELL_DELETE_STATE_POS]);

        case PROTOCOL_CAKE_DATA:
            return make_shared<CakeDTO>(input[CAKE_X_POS], input[CAKE_Y_POS],
                    input[CAKE_SIDE_LENGTH_POS]);

        case PROTOCOL_BUTTON_CHANGE_STATE:
            return make_shared<ButtonStateDTO>(input[BUTTON_CHANGE_ID_POS],
                    input[BUTTON_CHANGE_STATE_POS]);

        case PROTOCOL_ENERGY_TRANSMITTER_ACTIVATE:
            return make_shared<EnergyTransmitterActivateDTO>(input[ENRG_TRANSM_ACTV_ID_POS]);

        case PROTOCOL_ENERGY_RECEIVER_ACTIVATE:
            return make_shared<EnergyReceiverActivateDTO>(input[ENRG_RECVR_ACTV_ID_POS]);

        case PROTOCOL_GATE_CHANGE_STATE:
            return make_shared<GateStateDTO>(input[GATE_CHANGE_ID_POS],
                    input[GATE_CHANGE_STATE_POS]);

        default:    // Comando no existente en el protocolo
            return nullptr;
    }
}


void ProtocolTranslator::playerChellId(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (PlayerChellIdDTO*) dto;
    output.push_back(p_dto->getChellId());
}

void ProtocolTranslator::shootPortal(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (ShootPortalDTO*) dto;
    output.push_back(p_dto->getColor());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
}

void ProtocolTranslator::shootPinTool(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (ShootPinToolDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
}

void ProtocolTranslator::liftRock(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (LiftRockDTO*) dto;
    output.push_back(p_dto->getRockId());
}

void ProtocolTranslator::rockBlockData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (RockBlockDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
}

void ProtocolTranslator::metalBlockData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (MetalBlockDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
}

void ProtocolTranslator::metalDiagonalBlockData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (MetalDiagonalBlockDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getSideLength());
    output.push_back(p_dto->getOrientation());
}

void ProtocolTranslator::energyTransmitterData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (EnergyTransmitterDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getSideLength());
    output.push_back(p_dto->getDirection());
}

void ProtocolTranslator::energyReceiverData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (EnergyReceiverDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getSideLength());
}

void ProtocolTranslator::acidData(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (AcidDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
}


void ProtocolTranslator::buttonData(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (ButtonDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
}

void ProtocolTranslator::gateData(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (GateDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
}

void ProtocolTranslator::energyBarrierData(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (EnergyBarrierDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
}

void ProtocolTranslator::rockData(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (RockDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getSideLength());
    output.push_back(p_dto->getDeleteState());
}

void ProtocolTranslator::energyBallData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (EnergyBallDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getRadius());
    output.push_back(p_dto->getDeleteState());
}


void ProtocolTranslator::portalData(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (PortalDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
    output.push_back(p_dto->getColour());
    output.push_back(p_dto->getDeleteState());
}

void ProtocolTranslator::pinToolData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (PinToolDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
    output.push_back(p_dto->getDeleteState());
}

void ProtocolTranslator::chellData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (ChellDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
    output.push_back(p_dto->getDirection());
    output.push_back(p_dto->getTilted());
    output.push_back(p_dto->getMoving());
    output.push_back(p_dto->getJumping());
    output.push_back(p_dto->getShooting());
    output.push_back(p_dto->getCarryingRock());
    output.push_back(p_dto->getDeleteState());
}

void ProtocolTranslator::buttonState(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (ButtonStateDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getState());
}

void ProtocolTranslator::energyTransmitterActivate(const ProtocolDTO *dto,
        vector<int16_t> &output) {
    auto p_dto = (EnergyTransmitterActivateDTO*) dto;
    output.push_back(p_dto->getId());
}

void ProtocolTranslator::energyReceiverActivate(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (EnergyReceiverActivateDTO*) dto;
    output.push_back(p_dto->getId());
}

void ProtocolTranslator::gateState(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (GateStateDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getState());
}

void ProtocolTranslator::cakeData(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (CakeDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getSideLength());
}
