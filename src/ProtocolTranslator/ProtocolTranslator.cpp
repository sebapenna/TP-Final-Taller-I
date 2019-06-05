#include "ProtocolTranslator.h"
#include "PortalDTO.h"
#include "PinToolDTO.h"
#include "LiftRockDTO.h"
#include "MoveLeftDTO.h"
#include "MoveRightDTO.h"
#include "StopDTO.h"
#include "JumpDTO.h"
#include "DropRockDTO.h"
#include <src/constants.h>
#include <vector>

using std::vector;
using std::move;

vector<int> ProtocolTranslator::translate(const ProtocolDTO *dto) {
    switch (dto->getClassId()) {
        case PROTOCOL_MOVE_LEFT:
            return move(moveLeft(dto));
        case PROTOCOL_MOVE_RIGHT:
            return move(moveRight(dto));
        case PROTOCOL_JUMP:
            return move(jump(dto));
        case PROTOCOL_STOP:
            return move(stop(dto));
        case PROTOCOL_PORTAL:
            return move(portal(dto));
        case PROTOCOL_PIN_TOOL:
            return move(pinTool(dto));
        case PROTOCOL_LIFT_ROCK:
            return move(liftRock(dto));
        case PROTOCOL_DROP_ROCK:
            return move(dropRock(dto));
        default:
            // Este caso no existe
            break;
    }
}

vector<int> ProtocolTranslator::moveLeft(const ProtocolDTO *dto) {
    vector<int> v;
    v.push_back(PROTOCOL_MOVE_LEFT);
    return move(v);
}

std::vector<int> ProtocolTranslator::moveRight(const ProtocolDTO *dto) {
    vector<int> v;
    v.push_back(PROTOCOL_MOVE_RIGHT);
    return move(v);
}

std::vector<int> ProtocolTranslator::jump(const ProtocolDTO *dto) {
    vector<int> v;
    v.push_back(PROTOCOL_JUMP);
    return move(v);
}

std::vector<int> ProtocolTranslator::stop(const ProtocolDTO *dto) {
    vector<int> v;
    v.push_back(PROTOCOL_STOP);
    return move(v);
}

std::vector<int> ProtocolTranslator::portal(const ProtocolDTO *dto) {
    auto p_dto = (PortalDTO*) dto;
    vector<int> v;
    v.push_back(PROTOCOL_PORTAL);
    v.push_back(p_dto->getColor());
    v.push_back(p_dto->getX());
    v.push_back(p_dto->getY());
    return move(v);
}

std::vector<int> ProtocolTranslator::pinTool(const ProtocolDTO *dto) {
    auto p_dto = (PinToolDTO*) dto;
    vector<int> v;
    v.push_back(PROTOCOL_PIN_TOOL);
    v.push_back(p_dto->getX());
    v.push_back(p_dto->getY());
    return move(v);
}

std::vector<int> ProtocolTranslator::liftRock(const ProtocolDTO *dto) {
    auto p_dto = (LiftRockDTO*) dto;
    vector<int> v;
    v.push_back(PROTOCOL_LIFT_ROCK);
    v.push_back(p_dto->getRockId());
    return move(v);
}

std::vector<int> ProtocolTranslator::dropRock(const ProtocolDTO *dto) {
    vector<int> v;
    v.push_back(PROTOCOL_DROP_ROCK);
    return move(v);
}

ProtocolDTO *ProtocolTranslator::translate(std::vector<int> data) {
    int command = data.at(0);
    switch (command) {
        case PROTOCOL_MOVE_LEFT:
            return moveLeft(data);
        case PROTOCOL_MOVE_RIGHT:
            return moveRight(data);
        case PROTOCOL_JUMP:
            return jump(data);
        case PROTOCOL_STOP:
            return stop(data);
        case PROTOCOL_PORTAL:
            return portal(data);
        case PROTOCOL_PIN_TOOL:
            return pinTool(data);
        case PROTOCOL_LIFT_ROCK:
            return liftRock(data);
        case PROTOCOL_DROP_ROCK:
            return dropRock(data);
        default:
            // Este caso no existe
            break;
    }
}

ProtocolDTO *ProtocolTranslator::moveLeft(std::vector<int> data) {
    return (ProtocolDTO*) new MoveLeftDTO();
}

ProtocolDTO *ProtocolTranslator::moveRight(std::vector<int> data) {
    return (ProtocolDTO*) new MoveRightDTO();
}

ProtocolDTO *ProtocolTranslator::stop(std::vector<int> data) {
    return (ProtocolDTO*) new StopDTO();
}

ProtocolDTO *ProtocolTranslator::jump(std::vector<int> data) {
    return (ProtocolDTO*) new JumpDTO();
}

ProtocolDTO *ProtocolTranslator::portal(std::vector<int> data) {
    return (ProtocolDTO*) new PortalDTO(data.at(1), data.at(2), data.at(3));
}

ProtocolDTO *ProtocolTranslator::pinTool(std::vector<int> data) {
    return (ProtocolDTO*) new PinToolDTO(data.at(1), data.at(2));
}

ProtocolDTO *ProtocolTranslator::liftRock(std::vector<int> data) {
    return (ProtocolDTO*) new LiftRockDTO(data.at(1));
}

ProtocolDTO *ProtocolTranslator::dropRock(std::vector<int> data) {
    return (ProtocolDTO*) new DropRockDTO();
}

//
//shared_ptr<Dto*> ProtocolTranslator::process(std::vector<char> &msg) {
//
//}
