//
// Created by jonathanmedina on 04/06/19.
//

#include "Position.h"

Position::Position(int x, int y) : x(x), y(y){
}

int Position::getX() const {
    return this->x;
}

int Position::getY() const {
    return this->y;
}

void Position::set(int x, int y) {
    this->x = x;
    this->y = y;
}
