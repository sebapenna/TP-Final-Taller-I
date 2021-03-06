#include <Common/ProtocolTranslator/DataDTO/ChellDTO.h>
#include <Common/ProtocolTranslator/DataDTO/PlayerChellIdDTO.h>
#include <Common/ProtocolTranslator/PlayerActionsDTO/MoveRightDTO.h>
#include <Common/ProtocolTranslator/DataDTO/ButtonDTO.h>
#include <Common/ProtocolTranslator/DataDTO/ButtonStateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/GateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/RockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/MetalBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/RockBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/GateStateDTO.h>
#include <Server/Model/constants.h>
#include <Common/ProtocolTranslator/DataDTO/MetalDiagonalBlockDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyBarrierDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyReceiverActivateDTO.h>
#include <Common/ProtocolTranslator/DataDTO/EnergyReceiverDTO.h>
#include <Common/ProtocolTranslator/GameStateDTO/BeginDTO.h>
#include <Common/ProtocolTranslator/DataDTO/CakeDTO.h>
#include <Common/ProtocolTranslator/DataDTO/PortalDTO.h>
#include "FakeServer.h"
#include "Common/ProtocolTranslator/ProtocolDTO.h"

#include "Common/SafeQueue.h"

#define HALF_BOX_LEN 2
#define CHELL_HALF_WIDTH  HALF_BOX_LEN
#define CHELL_HALF_HEIGHT  HALF_BOX_LEN
#define ROCK_HALF_LEN  2
#define BUTTON_HALF_WIDTH  HALF_BOX_LEN
#define BUTTON_HALF_HEIGHT  0.25
#define GATE_HALF_WIDTH  HALF_BOX_LEN
#define GATE_HALF_HEIGHT  (2 * GATE_HALF_WIDTH)
#define ENRG_BLOCK_HALF_LEN  HALF_BOX_LEN
#define CAKE_HALF_LEN   2

FakeServer::FakeServer(ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>> &blockingQueue,
        SafeQueue<std::shared_ptr<ProtocolDTO>> &safeQueue, bool& done) :
        blockingQueue(blockingQueue), safeQueue(safeQueue), done(done) {
}

void FakeServer::run() {
    int x=0;
    std::shared_ptr<ProtocolDTO>dto(new ChellDTO(1, x, 4, CHELL_HALF_WIDTH*2, CHELL_HALF_HEIGHT*2, WEST, NOT_TILTED, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, DONT_DELETE));
    safeQueue.push(dto);
    /*std::shared_ptr<ProtocolDTO>dto2(new ChellDTO(2, 1, 5, 4, 4, WEST, NOT_TILTED, NOT_MOVING, JUMPING, NOT_SHOOTING, DONT_DELETE));
    safeQueue.push(dto2);
    */
    //std::shared_ptr<ProtocolDTO>dto3(new ChellDTO(2, -15, 4, CHELL_HALF_WIDTH*2, CHELL_HALF_HEIGHT*2, WEST, NOT_TILTED, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, DELETE));
    //safeQueue.push(dto3);
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
    std::shared_ptr<ProtocolDTO>dto33(new MetalBlockDTO(25, 4, 4, 150));
    safeQueue.push(dto33);
    std::shared_ptr<ProtocolDTO>dto34(new CakeDTO(20, 4, CAKE_HALF_LEN*2));
    safeQueue.push(dto34);
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
    std::shared_ptr<ProtocolDTO>dto812(new PortalDTO(0, 10, 4, 4,2, STRAIGHT, BLUE_PORTAL, DONT_DELETE));
    safeQueue.push(dto812);
    while (!done) {
        auto protocolDTO = blockingQueue.getTopAndPop();
        if (protocolDTO.get()->getClassId() == PROTOCOL_MOVE_LEFT) {
            x-=1;
            //safeQueue.push((void *) new ButtonStateDTO(1, PRESSED));
            std::shared_ptr<ProtocolDTO>dto9(new ChellDTO(1, x, 4, CHELL_HALF_WIDTH*2, CHELL_HALF_HEIGHT*2, WEST, NOT_TILTED, MOVING, NOT_JUMPING, NOT_SHOOTING, DONT_DELETE));
            safeQueue.push(dto9);
            /*std::shared_ptr<ProtocolDTO>dto11(new GateStateDTO(1, OPEN));
            std::shared_ptr<ProtocolDTO>dto10(new ButtonStateDTO(1, PRESSED));
            safeQueue.push(dto10);
            safeQueue.push(dto11);*/

        } else if (protocolDTO.get()->getClassId() == PROTOCOL_MOVE_RIGHT) {
            x+=1;
            std::shared_ptr<ProtocolDTO>dto9(new ChellDTO(1, x, 4, CHELL_HALF_WIDTH*2, CHELL_HALF_HEIGHT*2, EAST, NOT_TILTED, MOVING, NOT_JUMPING, NOT_SHOOTING, DONT_DELETE));
            safeQueue.push(dto9);

            /*std::shared_ptr<ProtocolDTO>dto10(new GateStateDTO(1, CLOSED));
            safeQueue.push(dto10);
            std::shared_ptr<ProtocolDTO>dto11(new ButtonStateDTO(1, NOT_PRESSED));
            safeQueue.push(dto11);

            std::shared_ptr<EnergyReceiverActivateDTO>dto99(new EnergyReceiverActivateDTO(1));
            safeQueue.push(dto99);*/
            //safeQueue.push((void *) new ButtonStateDTO(1, NOT_PRESSED));
        } else if (protocolDTO.get()->getClassId() == PROTOCOL_STOP) {
            std::shared_ptr<ProtocolDTO>dto9(new ChellDTO(1, x, 4, CHELL_HALF_WIDTH*2, CHELL_HALF_HEIGHT*2, EAST, NOT_TILTED, NOT_MOVING, NOT_JUMPING, NOT_SHOOTING, DONT_DELETE));
            safeQueue.push(dto9);
        }
    }
}
