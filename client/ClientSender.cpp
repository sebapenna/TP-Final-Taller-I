//
// Created by jonathanmedina on 10/06/19.
//

#include "ClientSender.h"

ClientSender::ClientSender(Protocol &protocol, ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>> &blockingQueue, bool& done) : protocol(protocol), blockingQueue(blockingQueue), done(done) {
}

void ClientSender::run() {
    while (!done) { // connected
        auto event = blockingQueue.getTopAndPop();
        auto dto = event.get();
        this->protocol<<*dto;
    }
}
