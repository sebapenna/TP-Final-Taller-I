//
// Created by jonathanmedina on 10/06/19.
//

#ifndef PORTAL_CLIENTRECEIVER_H
#define PORTAL_CLIENTRECEIVER_H


#include <Common/Thread.h>
#include <Common/ProtocolTranslator/ProtocolDTO.h>
#include <Common/SafeQueue.h>
#include <Common/Protocol.h>

class ClientReceiver : public Thread {
private:
    Protocol& protocol;
    SafeQueue<std::shared_ptr<ProtocolDTO>>& safeQueue;
    bool& done;
public:
    ClientReceiver(Protocol& protocol, SafeQueue<std::shared_ptr<ProtocolDTO>>& safeQueue, bool& done);
    void run() override;
};


#endif //PORTAL_CLIENTRECEIVER_H
