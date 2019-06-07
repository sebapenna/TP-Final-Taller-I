#include "ProtocolTranslator.h"
#include "ShootPortalDTO.h"
#include "ShootPinToolDTO.h"
#include "LiftRockDTO.h"
#include "MoveLeftDTO.h"
#include "MoveRightDTO.h"
#include "StopDTO.h"
#include "JumpDTO.h"
#include "DropRockDTO.h"
#include "PlayerChellIdDTO.h"
#include "RockBlockDTO.h"
#include "MetalBlockDTO.h"
#include "MetalDiagonalBlockDTO.h"
#include "EnergyTransmitterDTO.h"
#include "EnergyReceiverDTO.h"
#include "AcidDTO.h"
#include "ButtonDTO.h"
#include "GateDTO.h"
#include "EnergyBarrierDTO.h"
#include "RockDTO.h"
#include "EnergyBallDTO.h"
#include "PortalDTO.h"
#include "PinToolDTO.h"
#include "ChellDTO.h"
#include "ButtonStateDTO.h"
#include "EnergyTransmitterActivateDTO.h"
#include "EnergyReceiverActivateDTO.h"
#include "GateStateDTO.h"
#include <vector>
#include <iostream>

using std::vector;
using std::move;
using std::shared_ptr;
using std::make_shared;

/********************* DTO a Vector ************************/
int ProtocolTranslator::translate(const ProtocolDTO *dto, vector<int16_t> &output) {
    output.push_back(dto->getClassId());    // Siempre primer valor es el ID
    switch (dto->getClassId()) {
        case PROTOCOL_MOVE_LEFT:
            break;  // No tiene mas datos a agregar
        case PROTOCOL_MOVE_RIGHT:
            break;  // No tiene mas datos a agregar
        case PROTOCOL_JUMP:
            break;  // No tiene mas datos a agregar
        case PROTOCOL_STOP:
            break;  // No tiene mas datos a agregar
        case PROTOCOL_SHOOT_PORTAL:
            shootPortal(dto, output);
            break;
        case PROTOCOL_SHOOT_PIN_TOOL:
            shootPinTool(dto, output);
            break;
        case PROTOCOL_LIFT_ROCK:
            liftRock(dto, output);
            break;
        case PROTOCOL_DROP_ROCK:
            break;  // No tiene mas datos a agregar
        case PROTOCOL_PLAYER_CHELL_ID:
            playerChellId(dto, output);
            break;
        case PROTOCOL_ROCK_BLOCK_DATA:
            rockBlockData(dto, output);
            break;
        case PROTOCOL_METAL_BLOCK_DATA:
            metalBlockData(dto, output);
            break;
        case PROTOCOL_METAL_DIAGONAL_BLOCK_DATA:
            metalDiagonalBlockData(dto, output);
            break;
        case PROTOCOL_ENERGY_TRANSMITTER_DATA:
            energyTransmitterData(dto, output);
            break;
        case PROTOCOL_ENERGY_RECEIVER_DATA:
            energyReceiverData(dto, output);
            break;
        case PROTOCOL_ACID_DATA:
            acidData(dto ,output);
            break;
        case PROTOCOL_BUTTON_DATA:
            buttonData(dto, output);
            break;
        case PROTOCOL_GATE_DATA:
            gateData(dto, output);
            break;
        case PROTOCOL_ENERGY_BARRIER_DATA:
            energyBarrierData(dto, output);
            break;
        case PROTOCOL_ROCK_DATA:
            rockData(dto, output);
            break;
        case PROTOCOL_ENERGY_BALL_DATA:
            energyBallData(dto, output);
            break;
        case PROTOCOL_PORTAL_DATA:
            portalData(dto, output);
            break;
        case PROTOCOL_PIN_TOOL_DATA:
            pinToolData(dto, output);
            break;
        case PROTOCOL_CHELL_DATA:
            chellData(dto ,output);
            break;
        case PROTOCOL_BUTTON_CHANGE_STATE:
            buttonState(dto, output);
            break;
        case PROTOCOL_ENERGY_TRANSMITTER_ACTIVATE:
            energyTransmitterActivate(dto, output);
            break;
        case PROTOCOL_ENERGY_RECEIVER_ACTIVATE:
            energyReceiverActivate(dto, output);
            break;
        case PROTOCOL_GATE_CHANGE_STATE:
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
