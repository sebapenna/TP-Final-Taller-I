#ifndef TP2_PROTECTED_SCRIPTS_PRIORITY_QUEUE_H
#define TP2_PROTECTED_SCRIPTS_PRIORITY_QUEUE_H

#include <condition_variable>
#include <queue>

// Monitor de la cola bloqueante, responsable de agregar los elementos e
// interpretar los mismos controlando los posibles threads a traves de
// condition variable
class ProtectedBlockingQueue {
    std::queue<void*> _queue;
    std::condition_variable _cond_var;
    std::mutex _m;
    bool _pushing_finished;

    public:
        ProtectedBlockingQueue();

        // Setea que no hay mas elementos por agregar, se asegura que todos los
        // elementos hayan sido procesados
        void setFinishedAdding();

        // Agrega un elemeto a la cola
        void push(void *new_data);

        // Retorna un elemento de la cola y lo quita.
        // Retorna nullptr en caso que la cola este vacia
        void * getTopAndPop();
};

#endif //TP2_PROTECTED_SCRIPTS_PRIORITY_QUEUE_H
