#include <iostream>
#include <thread>
#include <string>
#include "ProtectedQueue.h"

ProtectedQueue::ProtectedQueue() {
    this->_pushing_finished = false;
}

void ProtectedQueue::setFinishedAdding() {
    std::unique_lock<std::mutex> lock(_m);
    this->_pushing_finished = true;
    this->_cond_var.notify_all();
}

void ProtectedQueue::push(void *new_data) {
    std::lock_guard<std::mutex> lock(_m);
    this->_queue.push(std::move(new_data));
    this->_cond_var.notify_one();
}

void * ProtectedQueue::getTopAndPop() {
    std::unique_lock<std::mutex> lock(_m);
    while (this->_queue.empty() && !_pushing_finished)
        this->_cond_var.wait(lock);
    void* aux = nullptr;
    if (!this->_queue.empty()) {
        aux = _queue.front();
        this->_queue.pop();
    }
    lock.unlock();  // Habilito a otro thread
    return aux;
}
