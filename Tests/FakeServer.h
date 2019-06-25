//
// Created by jonathanmedina on 05/06/19.
//

#ifndef SDL_FAKESERVER_H
#define SDL_FAKESERVER_H


#include "../Common/Thread.h"
#include "../Common/ProtectedBlockingQueue.h"
#include "../Common/SafeQueue.h"
#include <memory>

class FakeServer : public Thread {
    ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>>& blockingQueue;
    SafeQueue<std::shared_ptr<ProtocolDTO>>& safeQueue;
    bool& done;
public:
    FakeServer(ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>>& blockingQueue,
            SafeQueue<std::shared_ptr<ProtocolDTO>>& safeQueue, bool& done);
    void run() override;
};


#endif //SDL_FAKESERVER_H
