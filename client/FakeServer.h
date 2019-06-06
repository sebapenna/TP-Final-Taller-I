//
// Created by jonathanmedina on 05/06/19.
//

#ifndef SDL_FAKESERVER_H
#define SDL_FAKESERVER_H


#include "common/ProtectedBlockingQueue.h"
#include "common/SafeQueue.h"
#include "common/thread.h"

class FakeServer : public Thread {
    ProtectedBlockingQueue& blockingQueue;
    SafeQueue& safeQueue;
public:
    FakeServer(ProtectedBlockingQueue& blockingQueue, SafeQueue& safeQueue);
    void run() override;
};


#endif //SDL_FAKESERVER_H