//
// Created by jonathanmedina on 05/06/19.
//

#include "FakeChellNewPosition.h"

FakeChellNewPosition::FakeChellNewPosition(int id, int x, int y) : id(id), x(x), y(y){

}

FakeChellNewPosition::~FakeChellNewPosition() {

}

int FakeChellNewPosition::getClassId() const {
    return id;
}

int FakeChellNewPosition::getX() const {
    return x;
}

int FakeChellNewPosition::getY() const {
    return y;
}
