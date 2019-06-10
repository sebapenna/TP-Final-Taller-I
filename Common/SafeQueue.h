#ifndef PORTAL_PROTECTEDQUEUE_H
#define PORTAL_PROTECTEDQUEUE_H

#include <condition_variable>
#include <queue>
#include <memory>
#include <Common/ProtocolTranslator/ProtocolDTO.h>

// Monitor de la cola, responsable de agregar los elementos e
// interpretar los mismos controlando los posibles threads a traves de
// condition variable
class SafeQueue {
    std::queue<std::shared_ptr<ProtocolDTO>> _queue;
    std::mutex _m;

public:
    // Agrega un elemeto a la cola
    void push(std::shared_ptr<ProtocolDTO> new_data);

    // Retorna un elemento de la cola y lo quita.
    // Retorna nullptr en caso que la cola este vacia
    std::shared_ptr<ProtocolDTO>  getTopAndPop();
};


#endif //PORTAL_PROTECTEDQUEUE_H
