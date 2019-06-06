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
#include <vector>

using std::vector;
using std::move;

/********************* DTO a Vector ************************/
int ProtocolTranslator::translate(const ProtocolDTO *dto, vector<int16_t>
        &output) {
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
        default:    // Comando no existente en el protocolo
            output.clear(); // Elimino ID incorrecto
            return -1;
    }
    return output.size();
}

/********************* Vector a DTO ************************/
ProtocolDTO *ProtocolTranslator::translate(const vector<int16_t> &input) {
    int command = input.at(0);
    switch (command) {
        case PROTOCOL_MOVE_LEFT:
            return moveLeft(input);
        case PROTOCOL_MOVE_RIGHT:
            return moveRight(input);
        case PROTOCOL_JUMP:
            return jump(input);
        case PROTOCOL_STOP:
            return stop(input);
        case PROTOCOL_SHOOT_PORTAL:
            return shootPortal(input);
        case PROTOCOL_SHOOT_PIN_TOOL:
            return shootPinTool(input);
        case PROTOCOL_LIFT_ROCK:
            return liftRock(input);
        case PROTOCOL_DROP_ROCK:
            return dropRock(input);
        case PROTOCOL_PLAYER_CHELL_ID:
            return playerChellId(input);
        case PROTOCOL_ROCK_BLOCK_DATA:
            return rockBlockData(input);
        case PROTOCOL_METAL_BLOCK_DATA:
            return metalBlockData(input);
        case PROTOCOL_METAL_DIAGONAL_BLOCK_DATA:
            return metalDiagonalBlockData(input);
        case PROTOCOL_ENERGY_TRANSMITTER_DATA:
            return energyTransmitterData(input);
        case PROTOCOL_ENERGY_RECEIVER_DATA:
            return energyReceiverData(input);
        case PROTOCOL_ACID_DATA:
            return acidData(input);
        case PROTOCOL_BUTTON_DATA:
            return buttonData(input);
        case PROTOCOL_GATE_DATA:
            return gateData(input);
        case PROTOCOL_ENERGY_BARRIER_DATA:
            return energyBarrierData(input);
        case PROTOCOL_ROCK_DATA:
            return rockData(input);
        default:    // Comando no existente en el protocolo
            return nullptr;
    }
}


ProtocolDTO *ProtocolTranslator::moveLeft(const vector<int16_t> &input) {
    return (ProtocolDTO*) new MoveLeftDTO();
}

ProtocolDTO *ProtocolTranslator::moveRight(const vector<int16_t> &input) {
    return (ProtocolDTO*) new MoveRightDTO();
}

ProtocolDTO *ProtocolTranslator::stop(const vector<int16_t> &input) {
    return (ProtocolDTO*) new StopDTO();
}

ProtocolDTO *ProtocolTranslator::jump(const vector<int16_t> &input) {
    return (ProtocolDTO*) new JumpDTO();
}

ProtocolDTO *ProtocolTranslator::dropRock(const vector<int16_t> &input) {
    return (ProtocolDTO*) new DropRockDTO();
}

void ProtocolTranslator::playerChellId(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (PlayerChellIdDTO*) dto;
    output.push_back(p_dto->getChellId());
}

ProtocolDTO * ProtocolTranslator::playerChellId(const vector<int16_t> &input) {
    return (ProtocolDTO*) new PlayerChellIdDTO(input.at(PLAYER_CHELL_ID_POS));
}

void ProtocolTranslator::shootPortal(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (ShootPortalDTO*) dto;
    output.push_back(p_dto->getColor());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
}

ProtocolDTO *ProtocolTranslator::shootPortal(const vector<int16_t> &input) {
    return (ProtocolDTO*) new ShootPortalDTO(input[SHOOT_PORTAL_COLOR_POS],
                                             input[SHOOT_PORTAL_X_POS], input[SHOOT_PORTAL_Y_POS]);
}

void ProtocolTranslator::shootPinTool(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (ShootPinToolDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
}

ProtocolDTO *ProtocolTranslator::shootPinTool(const vector<int16_t> &input) {
    return (ProtocolDTO*) new ShootPinToolDTO(input.at(SHOOT_PT_X_POS),
                                              input.at(SHOOT_PT_Y_POS));
}

void ProtocolTranslator::liftRock(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (LiftRockDTO*) dto;
    output.push_back(p_dto->getRockId());
}

ProtocolDTO *ProtocolTranslator::liftRock(const vector<int16_t> &input) {
    return (ProtocolDTO*) new LiftRockDTO(input.at(LIFT_ROCK_ID_POS));
}

void ProtocolTranslator::rockBlockData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (RockBlockDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
}

ProtocolDTO *ProtocolTranslator::rockBlockData(const vector<int16_t> &input) {
    return (ProtocolDTO*) new RockBlockDTO(input[ROCK_BLOCK_X_POS],
            input[ROCK_BLOCK_Y_POS], input[ROCK_BLOCK_WIDTH_POS], input[ROCK_BLOCK_HEIGHT_POS]);
}

void ProtocolTranslator::metalBlockData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (MetalBlockDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
}

ProtocolDTO *ProtocolTranslator::metalBlockData(const vector<int16_t> &input) {
    return (ProtocolDTO*) new MetalBlockDTO(input[METAL_BLOCK_X_POS],
            input[METAL_BLOCK_Y_POS], input[METAL_BLOCK_WIDTH_POS], input[METAL_BLOCK_HEIGHT_POS]);
}

void ProtocolTranslator::metalDiagonalBlockData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (MetalDiagonalBlockDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getSideLength());
    output.push_back(p_dto->getOrientation());
}

ProtocolDTO *ProtocolTranslator::metalDiagonalBlockData(const vector<int16_t> &input) {
    return (ProtocolDTO*) new MetalDiagonalBlockDTO(input[METAL_DIAG_BLOCK_X_POS],
            input[METAL_DIAG_BLOCK_Y_POS], input[METAL_DIAG_BLOCK_SIDE_LEN_POS],
            input[METAL_DIAG_BLOCK_ORIENT_POS]);
}

void ProtocolTranslator::energyTransmitterData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (EnergyTransmitterDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getSideLength());
    output.push_back(p_dto->getDirection());
}

ProtocolDTO *ProtocolTranslator::energyTransmitterData(const std::vector<int16_t> &input) {
    return (ProtocolDTO*) new EnergyTransmitterDTO(input[ENRG_TRANSM_ID_POS],
            input[ENRG_TRANSM_X_POS], input[ENRG_TRANSM_Y_POS], input[ENRG_TRANSM_SIDE_LEN_POS],
            input[ENRG_TRANSM_DIRECTION_POS]);
}

void ProtocolTranslator::energyReceiverData(const ProtocolDTO *dto, vector<int16_t> &output) {
    auto p_dto = (EnergyReceiverDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getSideLength());
}

ProtocolDTO *ProtocolTranslator::energyReceiverData(const std::vector<int16_t> &input) {
    return (ProtocolDTO*) new EnergyReceiverDTO(input[ENRG_RECVR_ID_POS], input[ENRG_RECVR_X_POS],
            input[ENRG_RECVR_Y_POS], input[ENRG_RECVR_SIDE_LEN_POS]);
}

void ProtocolTranslator::acidData(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (AcidDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
}


ProtocolDTO *ProtocolTranslator::acidData(const std::vector<int16_t> &input) {
    return (ProtocolDTO*) new AcidDTO(input[ACID_X_POS], input[ACID_Y_POS], input[ACID_WIDTH_POS],
                                      input[ACID_HEIGHT_POS]);
}

void ProtocolTranslator::buttonData(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (ButtonDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
}

ProtocolDTO *ProtocolTranslator::buttonData(const std::vector<int16_t> &input) {
    return (ProtocolDTO*) new ButtonDTO(input[BUTTON_ID_POS], input[BUTTON_X_POS],
            input[BUTTON_Y_POS], input[BUTTON_WIDTH_POS], input[BUTTON_HEIGHT_POS]);
}

void ProtocolTranslator::gateData(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (GateDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
}

ProtocolDTO *ProtocolTranslator::gateData(const std::vector<int16_t> &input) {
    return (ProtocolDTO*) new GateDTO(input[GATE_ID_POS], input[GATE_X_POS],
                                        input[GATE_Y_POS], input[GATE_WIDTH_POS], input[GATE_HEIGHT_POS]);}

void ProtocolTranslator::energyBarrierData(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (EnergyBarrierDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getWidth());
    output.push_back(p_dto->getHeight());
}

ProtocolDTO *ProtocolTranslator::energyBarrierData(const std::vector<int16_t> &input) {
    return (ProtocolDTO*) new EnergyBarrierDTO(input[ENRG_BARRIER_X_POS],
            input[ENRG_BARRIER_Y_POS], input[ENRG_BARRIER_WIDTH_POS],
            input[ENRG_BARRIER_HEIGHT_POS]);
}

void ProtocolTranslator::rockData(const ProtocolDTO *dto, std::vector<int16_t> &output) {
    auto p_dto = (RockDTO*) dto;
    output.push_back(p_dto->getId());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
    output.push_back(p_dto->getSideLength());
    output.push_back(p_dto->getDeleteState());
}

ProtocolDTO *ProtocolTranslator::rockData(const std::vector<int16_t> &input) {
    return (ProtocolDTO*) new RockDTO(input[ROCK_ID_POS], input[ROCK_X_POS], input[ROCK_Y_POS],
            input[ROCK_SIDE_LEN_POS], input[ROCK_DELETE_STATE_POS]);
}
//
//shared_ptr<Dto*> ProtocolTranslator::process(vector<char> &msg) {
//
//}
