//
// Created by jonathanmedina on 06/06/19.
//

#ifndef PORTAL_FAKECHELLNEWPOSITION_H
#define PORTAL_FAKECHELLNEWPOSITION_H


class FakeChellNewPosition {
    int id;
    int x;
    int y;
public:
    FakeChellNewPosition(int id, int x, int y);

    int getId() const;

    int getX() const;

    int getY() const;
};


#endif //PORTAL_FAKECHELLNEWPOSITION_H
