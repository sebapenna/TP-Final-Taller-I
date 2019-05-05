#ifndef TP_FINAL_POSICION_H
#define TP_FINAL_POSICION_H

class Posicion {
private:
    int _x;
    int _y;


public:
    bool igualA(const Posicion& other);

    void operator = (const Posicion& other);
};


#endif //TP_FINAL_POSICION_H
