#ifndef TP_FINAL_POSICION_H
#define TP_FINAL_POSICION_H

class Posicion {
private:
    int _x;
    int _y;


public:
    Posicion() = default;

    Posicion(int x, int y);

    bool igualA(const Posicion& other);

    int getX() const;

    int getY() const;

    void operator = (const Posicion& other);
};


#endif //TP_FINAL_POSICION_H
