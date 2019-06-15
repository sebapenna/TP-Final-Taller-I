//
// Created by jonathanmedina on 15/06/19.
//

#ifndef PORTAL_COMMANDSENDER_H
#define PORTAL_COMMANDSENDER_H

#include <Common/Protocol.h>
#include <Common/Thread.h>

class CommandSender : public Thread {
private:
    Protocol& protocol;
    bool& done;
    bool& user_quit;
public:
    CommandSender(Protocol &protocol, bool &done, bool &user_quit);

    void run() override;
};


#endif //PORTAL_COMMANDSENDER_H
