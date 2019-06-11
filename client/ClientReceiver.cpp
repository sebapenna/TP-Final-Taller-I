//
// Created by jonathanmedina on 10/06/19.
//

#include "ClientReceiver.h"


ClientReceiver::ClientReceiver(Protocol &protocol, SafeQueue<std::shared_ptr<ProtocolDTO>> &safeQueue, bool& done) : protocol(protocol), safeQueue(safeQueue), done(done) {
}

void ClientReceiver::run() {
    while (!done) { // connected;
        std::shared_ptr<ProtocolDTO> dto;
        protocol>>dto;
        safeQueue.push(dto);
    }
}
