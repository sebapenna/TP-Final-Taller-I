#include <iostream>
#include <thread>
#include <string>
#include "ProtectedBlockingQueue.h"

ProtectedBlockingQueue::ProtectedBlockingQueue() {
    this->_pushing_finished = false;
}

void ProtectedBlockingQueue::setFinishedAdding() {
    std::unique_lock<std::mutex> lock(_m);
    this->_pushing_finished = true;
    this->_cond_var.notify_all();
}

void ProtectedBlockingQueue::push(std::shared_ptr<ProtocolDTO> new_data) {
    std::lock_guard<std::mutex> lock(_m);
    this->_queue.push(std::move(new_data));
    this->_cond_var.notify_one();
}

std::shared_ptr<ProtocolDTO> ProtectedBlockingQueue::getTopAndPop() {
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
