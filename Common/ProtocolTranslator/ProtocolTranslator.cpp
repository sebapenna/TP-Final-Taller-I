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
#include <vector>

using std::vector;
using std::move;

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
        default:    // Comando no existente en el protocolo
            output.clear(); // Elimino ID incorrecto
            return -1;
    }
    return output.size();
}

void ProtocolTranslator::playerChellId(const ProtocolDTO *dto,
                                       vector<int16_t> &output) {
    auto p_dto = (PlayerChellIdDTO*) dto;
    output.push_back(p_dto->getChellId());
}

void ProtocolTranslator::shootPortal(const ProtocolDTO *dto,
                                vector<int16_t> &output) {
    auto p_dto = (ShootPortalDTO*) dto;
    output.push_back(p_dto->getColor());
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
}

void ProtocolTranslator::shootPinTool(const ProtocolDTO *dto,
                                 vector<int16_t> &output) {
    auto p_dto = (ShootPinToolDTO*) dto;
    output.push_back(p_dto->getX());
    output.push_back(p_dto->getY());
}

void ProtocolTranslator::liftRock(const ProtocolDTO *dto,
                                  vector<int16_t> &output) {
    auto p_dto = (LiftRockDTO*) dto;
    output.push_back(p_dto->getRockId());
}

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

ProtocolDTO *ProtocolTranslator::shootPortal(const vector<int16_t> &input) {
    return (ProtocolDTO*) new ShootPortalDTO(input[SHOOT_PORTAL_COLOR_POS],
            input[SHOOT_PORTAL_X_POS], input[SHOOT_PORTAL_Y_POS]);
}

ProtocolDTO *ProtocolTranslator::shootPinTool(const vector<int16_t> &input) {
    return (ProtocolDTO*) new ShootPinToolDTO(input.at(SHOOT_PT_X_POS),
            input.at(SHOOT_PT_Y_POS));
}

ProtocolDTO *ProtocolTranslator::liftRock(const vector<int16_t> &input) {
    return (ProtocolDTO*) new LiftRockDTO(input.at(LIFT_ROCK_ID_POS));
}

ProtocolDTO *ProtocolTranslator::dropRock(const vector<int16_t> &input) {
    return (ProtocolDTO*) new DropRockDTO();
}

ProtocolDTO * ProtocolTranslator::playerChellId(const std::vector<int16_t>
        &input) {
    return (ProtocolDTO*) new PlayerChellIdDTO(input.at(PLAYER_CHELL_ID_POS));
}

//
//shared_ptr<Dto*> ProtocolTranslator::process(vector<char> &msg) {
//
//}
