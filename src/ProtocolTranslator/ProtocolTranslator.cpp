#include "ProtocolTranslator.h"
#include "PortalDTO.h"
#include "PinToolDTO.h"
#include "LiftRockDTO.h"
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

//
//shared_ptr<Dto*> ProtocolTranslator::process(std::vector<char> &msg) {
//
//}
