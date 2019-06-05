#include "SafeQueue.h"
#include <thread>
#include <string>

void SafeQueue::push(void *new_data) {
    std::lock_guard<std::mutex> lock(_m);
    this->_queue.push(std::move(new_data));
}

void * SafeQueue::getTopAndPop() {
    std::unique_lock<std::mutex> lock(_m);
    void* aux = nullptr;
    if (!this->_queue.empty()) {
        aux = _queue.front();
        this->_queue.pop();
    }
    lock.unlock();  // Habilito a otro thread
    return aux;
}