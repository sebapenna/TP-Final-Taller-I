//
// Created by jonathanmedina on 05/06/19.
//

#include "FakeServer.h"
#include "../Common/ProtocolTranslator/ProtocolDTO.h"
#include "FakeChellNewPosition.h"
#include "../Common/SafeQueue.h"

FakeServer::FakeServer(ProtectedBlockingQueue &blockingQueue, SafeQueue &safeQueue) : blockingQueue(blockingQueue), safeQueue(safeQueue) {

}

void FakeServer::run() {
    int x=200;
    //safeQueue.push((void *) new FakeChellNewPosition(1,x,200));
    safeQueue.push((void *) new FakeChellNewPosition(2,-200,-100));
    safeQueue.push((void *) new FakeChellNewPosition(3,100,-100));
    while (true) {
        x+=10;
        ProtocolDTO* protocolDTO = (ProtocolDTO*) blockingQueue.getTopAndPop();
        safeQueue.push((void *) new FakeChellNewPosition(1,x,200));

        //  Aca desencolar cosas de la blocking queue, y encolarlas en la safe queue.
    }
}
