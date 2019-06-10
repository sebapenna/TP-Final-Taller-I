#ifndef PORTAL_RECEIVERTHREAD_H
#define PORTAL_RECEIVERTHREAD_H

#include <thread>
#include <Common/SafeQueue.h>
#include "Player.h"

// Thread exclusivo recibir datos por parte del player indicado en el constructor y encolarlos en
//  la cola de eventos
class ReceiverThread {
private:
    std::thread _thread;
    Player &_player;
    bool _dead = false;

    // Ejecuta las acciones entre player y events_queue. Finaliza cuando cliente se desconecta
    void run(Player &player,
            SafeQueue<std::pair<size_t, std::shared_ptr<ProtocolDTO>>> &events_queue);

public:
    ReceiverThread(Player &player,
            SafeQueue<std::pair<size_t, std::shared_ptr<ProtocolDTO>>>&events_queue);

    void join();

    size_t getPlayerId();

    bool isDead() const;
};


#endif //PORTAL_RECEIVERTHREAD_H
