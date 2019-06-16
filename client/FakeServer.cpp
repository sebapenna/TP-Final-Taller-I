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
#include <Common/ProtocolTranslator/EnergyBarrierDTO.h>
#include <Common/ProtocolTranslator/EnergyReceiverActivateDTO.h>
#include <Common/ProtocolTranslator/EnergyReceiverDTO.h>
#include <Common/ProtocolTranslator/ConnectionDTO/BeginDTO.h>
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
    int x=0;
    std::shared_ptr<ProtocolDTO>dto(new ChellDTO(1, x, 4, CHELL_HALF_WIDTH*2, CHELL_HALF_HEIGHT*2, WEST, NOT_TILTED, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
    safeQueue.push(dto);
    /*std::shared_ptr<ProtocolDTO>dto2(new ChellDTO(2, 1, 5, 4, 4, WEST, NOT_TILTED, NOT_MOVING, JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
    safeQueue.push(dto2);
    */
    std::shared_ptr<ProtocolDTO>dto3(new ChellDTO(2, -15, 4, CHELL_HALF_WIDTH*2, CHELL_HALF_HEIGHT*2, WEST, NOT_TILTED, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DELETE));
    safeQueue.push(dto3);
    std::shared_ptr<ProtocolDTO>dto4(new ButtonDTO(1, 10, 4, BUTTON_HALF_WIDTH*2, BUTTON_HALF_HEIGHT*2));
    safeQueue.push(dto4);
    std::shared_ptr<ProtocolDTO>dto5(new GateDTO(1, -1, 4, GATE_HALF_WIDTH*2, GATE_HALF_HEIGHT*2));
    safeQueue.push(dto5);
    std::shared_ptr<ProtocolDTO>dto6(new PlayerChellIdDTO(1));
    safeQueue.push(dto6);
    std::shared_ptr<ProtocolDTO>dto7(new RockDTO(3, 7, 4, ROCK_HALF_LEN*2, DONT_DELETE));
    safeQueue.push(dto7);
    std::shared_ptr<ProtocolDTO>dto8(new MetalBlockDTO(-50,0,300,4));
    safeQueue.push(dto8);
    /*
    std::shared_ptr<ProtocolDTO>dto8(new RockDTO(1, 500, 400, 128, DONT_DELETE));
    safeQueue.push(dto8);*/
    std::shared_ptr<EnergyReceiverDTO>dto16(new EnergyReceiverDTO(1, -20, 4, ENRG_BLOCK_HALF_LEN*2));
    safeQueue.push(dto16);
    std::shared_ptr<EnergyBarrierDTO>dto17(new EnergyBarrierDTO(15,4,1,20));
    safeQueue.push(dto17);
    std::shared_ptr<ProtocolDTO>dto18(new MetalDiagonalBlockDTO(-90, 4, 4, O_SE));
    safeQueue.push(dto18);
    std::shared_ptr<ProtocolDTO>dto19(new MetalDiagonalBlockDTO(-10, 4, 4, O_NO));
    safeQueue.push(dto19);

    std::shared_ptr<ProtocolDTO>dto999(new BeginDTO());
    safeQueue.push(dto999);
    while (!done) {
        auto protocolDTO = blockingQueue.getTopAndPop();
        if (protocolDTO.get()->getClassId() == PROTOCOL_MOVE_LEFT) {
            x-=1;
            //safeQueue.push((void *) new ButtonStateDTO(1, PRESSED));
            std::shared_ptr<ProtocolDTO>dto9(new ChellDTO(1, x, 4, CHELL_HALF_WIDTH*2, CHELL_HALF_HEIGHT*2, WEST, NOT_TILTED, MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
            safeQueue.push(dto9);

            /*std::shared_ptr<ProtocolDTO>dto11(new GateStateDTO(1, OPEN));
            std::shared_ptr<ProtocolDTO>dto10(new ButtonStateDTO(1, PRESSED));
            safeQueue.push(dto10);
            safeQueue.push(dto11);*/

        } else if (protocolDTO.get()->getClassId() == PROTOCOL_MOVE_RIGHT) {
            x+=1;
            std::shared_ptr<ProtocolDTO>dto9(new ChellDTO(1, x, 4, CHELL_HALF_WIDTH*2, CHELL_HALF_HEIGHT*2, EAST, NOT_TILTED, MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
            safeQueue.push(dto9);

            /*std::shared_ptr<ProtocolDTO>dto10(new GateStateDTO(1, CLOSED));
            safeQueue.push(dto10);
            std::shared_ptr<ProtocolDTO>dto11(new ButtonStateDTO(1, NOT_PRESSED));
            safeQueue.push(dto11);

            std::shared_ptr<EnergyReceiverActivateDTO>dto99(new EnergyReceiverActivateDTO(1));
            safeQueue.push(dto99);*/
            //safeQueue.push((void *) new ButtonStateDTO(1, NOT_PRESSED));
        } else if (protocolDTO.get()->getClassId() == PROTOCOL_STOP) {
            std::shared_ptr<ProtocolDTO>dto9(new ChellDTO(1, x, 4, CHELL_HALF_WIDTH*2, CHELL_HALF_HEIGHT*2, EAST, NOT_TILTED, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, NOT_CARRYING, DONT_DELETE));
            safeQueue.push(dto9);
        }
    }
}
