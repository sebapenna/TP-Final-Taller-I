//
// Created by jonathanmedina on 05/06/19.
//

#ifndef SDL_FAKECHELLNEWPOSITION_H
#define SDL_FAKECHELLNEWPOSITION_H


#include "ProtocolDTO.h"

class FakeChellNewPosition : public ProtocolDTO {
    int id;
    int x;
    int y;
public:
    FakeChellNewPosition(int id, int x, int y);
    ~FakeChellNewPosition() override;
    int getClassId() const override;
    int getX() const;
    int getY() const;
};


#endif //SDL_FAKECHELLNEWPOSITION_H
