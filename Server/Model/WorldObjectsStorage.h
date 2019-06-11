#ifndef PORTAL_WORLDOBJECTSSTORAGE_H
#define PORTAL_WORLDOBJECTSSTORAGE_H

#include <vector>

template <class T>
class WorldObjectsStorage {
private:
    std::vector<T> _vector;

public:
    void push_back(T e) {
        _vector.push_back(e);
    }

    T at(const size_t & i) {
        if (i >= _vector.size())
            return nullptr;
        return _vector.at(i);
    }


};


#endif //PORTAL_WORLDOBJECTSSTORAGE_H
