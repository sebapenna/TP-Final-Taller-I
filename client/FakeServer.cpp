//
// Created by jonathanmedina on 05/06/19.
//

#include <Common/ProtocolTranslator/ChellDTO.h>
#include <Common/ProtocolTranslator/PlayerChellIdDTO.h>
#include <Common/ProtocolTranslator/MoveRightDTO.h>
#include <Common/ProtocolTranslator/ButtonDTO.h>
#include <Common/ProtocolTranslator/ButtonStateDTO.h>
#include "FakeServer.h"
#include "../Common/ProtocolTranslator/ProtocolDTO.h"

#include "../Common/SafeQueue.h"

FakeServer::FakeServer(ProtectedBlockingQueue &blockingQueue, SafeQueue &safeQueue) : blockingQueue(blockingQueue), safeQueue(safeQueue) {

}

void FakeServer::run() {
    int x=200;
    safeQueue.push((void *) new ChellDTO(1, x, 200, 201, 220, WEST, NOT_TILTED, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
    safeQueue.push((void *) new ChellDTO(2, -200, -100, 201, 220, WEST, NOT_TILTED, NOT_MOVING, JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
    safeQueue.push((void *) new ChellDTO(3, 100, -100, 201, 220, WEST, NOT_TILTED, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DELETE));
    safeQueue.push((void *) new ButtonDTO(1, -200, 360, 200, 50));
    safeQueue.push((void *) new PlayerChellIdDTO(1));

    while (true) {
        auto protocolDTO = (ProtocolDTO*) blockingQueue.getTopAndPop();
        if (protocolDTO->getClassId() == PROTOCOL_MOVE_LEFT) {
            x-=10;
            //safeQueue.push((void *) new ButtonStateDTO(1, PRESSED));
            safeQueue.push((void *) new ChellDTO(1,x,200, 201, 220, WEST, NOT_TILTED, MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
        } else if (protocolDTO->getClassId() == PROTOCOL_MOVE_RIGHT) {
            x+=10;
            safeQueue.push((void *) new ChellDTO(1,x,200, 201, 220, EAST, NOT_TILTED, MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
            //safeQueue.push((void *) new ButtonStateDTO(1, NOT_PRESSED));
        } else if (protocolDTO->getClassId() == PROTOCOL_STOP) {
            safeQueue.push((void *) new ChellDTO(1,x,200, 201, 220, EAST, NOT_TILTED, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
        }
    }
}
