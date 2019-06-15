//
// Created by jonathanmedina on 15/06/19.
//

#ifndef PORTAL_COMMANDRECEIVER_H
#define PORTAL_COMMANDRECEIVER_H


#include <Common/Protocol.h>
#include <Common/Thread.h>

class CommandReceiver : public Thread {
private:
    Protocol& protocol;
    bool& done;
    bool& user_quit;
public:
    CommandReceiver(Protocol &protocol, bool& done, bool& user_quit);
    void run() override;
};


#endif //PORTAL_COMMANDRECEIVER_H
