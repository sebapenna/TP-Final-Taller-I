#ifndef PORTAL_PROTECTEDQUEUE_H
#define PORTAL_PROTECTEDQUEUE_H

#include <condition_variable>
#include <queue>
#include <memory>
#include <Common/ProtocolTranslator/ProtocolDTO.h>

// Monitor de la cola, responsable de agregar los elementos e
// interpretar los mismos controlando los posibles threads a traves de
// condition variable
template <class T>
class SafeQueue {
    std::queue<T> _queue;
    std::mutex _m;

public:
    // Agrega un elemeto a la cola
    void push(T new_data) {
        std::lock_guard<std::mutex> lock(_m);
        this->_queue.push(std::move(new_data));
    }

    // Retorna un elemento de la cola y lo quita.
    // Retorna nullptr en caso que la cola este vacia
    T  getTopAndPop() {
        std::lock_guard<std::mutex> lock(_m);
        T  aux = nullptr;
        if (!this->_queue.empty()) {
            aux = _queue.front();
            this->_queue.pop();
        }
        return aux;
    }
};


#endif //PORTAL_PROTECTEDQUEUE_H
