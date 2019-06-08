//
// Created by jonathanmedina on 04/06/19.
//

#ifndef SDL_POSITION_H
#define SDL_POSITION_H



class Position {
private:
    int x;
    int y;
public:
    Position(int x, int y);
    int getX() const;
    int getY() const;
    void set(int x, int y);

};


#endif //SDL_POSITION_H
