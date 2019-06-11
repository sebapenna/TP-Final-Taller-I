//
// Created by jonathanmedina on 10/06/19.
//

#ifndef PORTAL_CLIENTSENDER_H
#define PORTAL_CLIENTSENDER_H


#include <Common/Thread.h>
#include <Common/Protocol.h>
#include <Common/ProtectedBlockingQueue.h>

class ClientSender : public Thread {
private:
    Protocol& protocol;
    ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>>& blockingQueue;
    bool& done;
public:
    ClientSender(Protocol& protocol, ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>>& blockingQueue, bool& done);
    void run() override;
};


#endif //PORTAL_CLIENTSENDER_H
