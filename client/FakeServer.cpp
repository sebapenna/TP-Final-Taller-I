//
// Created by jonathanmedina on 05/06/19.
//

#include <Common/ProtocolTranslator/ChellDTO.h>
#include <Common/ProtocolTranslator/PlayerChellIdDTO.h>
#include <Common/ProtocolTranslator/MoveRightDTO.h>
#include <Common/ProtocolTranslator/ButtonDTO.h>
#include <Common/ProtocolTranslator/ButtonStateDTO.h>
#include <Common/ProtocolTranslator/GateDTO.h>
#include <Common/ProtocolTranslator/RockDTO.h>
#include <Common/ProtocolTranslator/MetalBlockDTO.h>
#include <Common/ProtocolTranslator/RockBlockDTO.h>
#include <Common/ProtocolTranslator/GateStateDTO.h>
#include <Server/Model/constants.h>
#include <Common/ProtocolTranslator/MetalDiagonalBlockDTO.h>
#include "FakeServer.h"
#include "../Common/ProtocolTranslator/ProtocolDTO.h"

#include "../Common/SafeQueue.h"

FakeServer::FakeServer(ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>> &blockingQueue,
        SafeQueue<std::shared_ptr<ProtocolDTO>> &safeQueue, bool& done) :
        blockingQueue(blockingQueue), safeQueue(safeQueue), done(done) {
}

void FakeServer::run() {
    /*for (int startX = -2000; startX<7000; startX+=128) {
        for (int startY = -2000; startY<7000; startY+=128) {
            safeQueue.push((void*) new RockBlockDTO(startX, startY, 128, 128));
        }
        //safeQueue.push((void*) new MetalBlockDTO(startX, 400, 128,128));
    }*/
    int x=200;
    std::shared_ptr<ProtocolDTO>dto(new ChellDTO(1, x, 200, 201, 220, WEST, NOT_TILTED, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
    safeQueue.push(dto);
    std::shared_ptr<ProtocolDTO>dto2(new ChellDTO(2, -200, -100, 201, 220, WEST, NOT_TILTED, NOT_MOVING, JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
    safeQueue.push(dto2);
    std::shared_ptr<ProtocolDTO>dto3(new ChellDTO(3, 100, -100, 201, 220, WEST, NOT_TILTED, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DELETE));
    safeQueue.push(dto3);
    std::shared_ptr<ProtocolDTO>dto4(new ButtonDTO(1, -200, 360, 200, 50));
    safeQueue.push(dto4);
    std::shared_ptr<ProtocolDTO>dto5(new GateDTO(1, 400, 200, 200, 350));
    safeQueue.push(dto5);
    std::shared_ptr<ProtocolDTO>dto6(new PlayerChellIdDTO(1));
    safeQueue.push(dto6);
    std::shared_ptr<ProtocolDTO>dto7(new RockDTO(3, 0, 400, 128, DONT_DELETE));
    safeQueue.push(dto7);
    std::shared_ptr<ProtocolDTO>dto8(new RockDTO(1, 500, 400, 128, DONT_DELETE));
    safeQueue.push(dto8);
    std::shared_ptr<ProtocolDTO>dto18(new MetalDiagonalBlockDTO(100, 500, 128, O_SE));
    safeQueue.push(dto18);
    std::shared_ptr<ProtocolDTO>dto19(new MetalDiagonalBlockDTO(100, 300, 128, O_NO));
    safeQueue.push(dto19);

    std::shared_ptr<ProtocolDTO>dto20(new ChellDTO(4, 100, -100, 201, 220, WEST, O_O, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
    safeQueue.push(dto20);
    while (!done) {
        auto protocolDTO = blockingQueue.getTopAndPop();
        if (protocolDTO.get()->getClassId() == PROTOCOL_MOVE_LEFT) {
            x-=10;
            //safeQueue.push((void *) new ButtonStateDTO(1, PRESSED));
            std::shared_ptr<ProtocolDTO>dto9(new ChellDTO(1,x,200, 201, 220, WEST, NOT_TILTED, MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
            safeQueue.push(dto9);
            std::shared_ptr<ProtocolDTO>dto10(new GateStateDTO(1, OPEN));
            safeQueue.push(dto10);
        } else if (protocolDTO.get()->getClassId() == PROTOCOL_MOVE_RIGHT) {
            x+=10;
            std::shared_ptr<ProtocolDTO>dto9(new ChellDTO(1,x,200, 201, 220, EAST, NOT_TILTED, MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
            safeQueue.push(dto9);
            std::shared_ptr<ProtocolDTO>dto10(new GateStateDTO(1, CLOSED));
            safeQueue.push(dto10);
            //safeQueue.push((void *) new ButtonStateDTO(1, NOT_PRESSED));
        } else if (protocolDTO.get()->getClassId() == PROTOCOL_STOP) {
            std::shared_ptr<ProtocolDTO>dto9(new ChellDTO(1,x,200, 201, 220, EAST, NOT_TILTED, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
            safeQueue.push(dto9);
        }
    }
}
