#ifndef PORTAL_RECEIVERTHREAD_H
#define PORTAL_RECEIVERTHREAD_H

#include <thread>
#include <Common/SafeQueue.h>
#include "Event.h"

class Player;
class Lobby;

// Thread exclusivo recibir datos por parte del player indicado en el constructor y encolarlos en
//  la cola de eventos
class ReceiverThread {
private:
    std::thread _thread;
    std::shared_ptr<Player> _player;
    bool _dead = false;

    // Recibe los DTO provenientes de player y los encola para ser posteriormente aplicados
    // al modelo. Finaliza cuando cliente se desconecta
    void run(Lobby &lobby/*std::shared_ptr<Player> player*/);

public:
    explicit ReceiverThread(std::shared_ptr<Player> player, Lobby &lobby);

    void join();

    size_t getPlayerId();

    bool isDead() const;
};


#endif //PORTAL_RECEIVERTHREAD_H
