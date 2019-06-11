#include <utility>

#include "Event.h"

Event::Event(const size_t &id, std::shared_ptr<ProtocolDTO> ptr) :_id(id) {
    _ptr = std::move(ptr);
}

const size_t Event::getId() const {
    return _id;
}

const std::shared_ptr<ProtocolDTO> &Event::getPtr() const {
    return _ptr;
}
