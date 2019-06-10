#ifndef TP2_PROTECTED_SCRIPTS_PRIORITY_QUEUE_H
#define TP2_PROTECTED_SCRIPTS_PRIORITY_QUEUE_H

#include <condition_variable>
#include <queue>
#include <Common/ProtocolTranslator/ProtocolDTO.h>

// Monitor de la cola bloqueante, responsable de agregar los elementos e
// interpretar los mismos controlando los posibles threads a traves de
// condition variable
template <class T>
class ProtectedBlockingQueue {
    std::queue<T> _queue;
    std::condition_variable _cond_var;
    std::mutex _m;
    bool _pushing_finished;

    public:
        ProtectedBlockingQueue() {
            _pushing_finished = false;
        }

        // Setea que no hay mas elementos por agregar, se asegura que todos los
        // elementos hayan sido procesados
        void setFinishedAdding() {
            std::unique_lock<std::mutex> lock(_m);
            this->_pushing_finished = true;
            this->_cond_var.notify_all();
        }

        // Agrega un elemeto a la cola
        void push(T new_data) {
            std::lock_guard<std::mutex> lock(_m);
            this->_queue.push(std::move(new_data));
            this->_cond_var.notify_one();
        }

        // Retorna un elemento de la cola y lo quita.
        // Retorna nullptr en caso que la cola este vacia
        T getTopAndPop() {
            std::unique_lock<std::mutex> lock(_m);
            while (this->_queue.empty() && !_pushing_finished)
                this->_cond_var.wait(lock);
            std::shared_ptr<ProtocolDTO> aux = nullptr;
            if (!this->_queue.empty()) {
                aux = _queue.front();
                this->_queue.pop();
            }
            lock.unlock();  // Habilito a otro thread
            return aux;
        }
};

#endif //TP2_PROTECTED_SCRIPTS_PRIORITY_QUEUE_H
