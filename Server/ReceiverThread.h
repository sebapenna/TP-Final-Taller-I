#ifndef PORTAL_RECEIVERTHREAD_H
#define PORTAL_RECEIVERTHREAD_H

#include <thread>
#include <Common/SafeQueue.h>
#include "Player.h"
#include "Event.h"

// Thread exclusivo recibir datos por parte del player indicado en el constructor y encolarlos en
//  la cola de eventos
class ReceiverThread {
private:
    std::thread _thread;
    std::shared_ptr<Player> _player;
    bool _dead = false;

    // Recibe los DTO provenientes de player y los encola para ser posteriormente aplicados
    // al modelo. Finaliza cuando cliente se desconecta
    void run(std::shared_ptr<Player> player, SafeQueue<std::shared_ptr<Event>> &events_queue);

public:
    ReceiverThread(std::shared_ptr<Player> player, SafeQueue<std::shared_ptr<Event>> &events_queue);

    void join();

    size_t getPlayerId();

    bool isDead() const;
};


#endif //PORTAL_RECEIVERTHREAD_H
