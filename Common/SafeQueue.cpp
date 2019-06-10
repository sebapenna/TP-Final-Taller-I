#include "SafeQueue.h"
#include <thread>
#include <string>

void SafeQueue::push(std::shared_ptr<ProtocolDTO> new_data) {
    std::lock_guard<std::mutex> lock(_m);
    this->_queue.push(std::move(new_data));
}

std::shared_ptr<ProtocolDTO>  SafeQueue::getTopAndPop() {
    std::lock_guard<std::mutex> lock(_m);
    std::shared_ptr<ProtocolDTO>  aux = nullptr;
    if (!this->_queue.empty()) {
        aux = _queue.front();
        this->_queue.pop();
    }
    return aux;
}