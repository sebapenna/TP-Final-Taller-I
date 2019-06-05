#ifndef PORTAL_PROTECTEDQUEUE_H
#define PORTAL_PROTECTEDQUEUE_H

#include <condition_variable>
#include <queue>

// Monitor de la cola, responsable de agregar los elementos e
// interpretar los mismos controlando los posibles threads a traves de
// condition variable
class ProtectedBlockingQueue {
    std::queue<void*> _queue;
    std::mutex _m;

public:
    // Agrega un elemeto a la cola
    void push(void *new_data);

    // Retorna un elemento de la cola y lo quita.
    // Retorna nullptr en caso que la cola este vacia
    void * getTopAndPop();
};


#endif //PORTAL_PROTECTEDQUEUE_H
