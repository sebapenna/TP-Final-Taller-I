#ifndef TP_FINAL_EJEMPLO_H
#define TP_FINAL_EJEMPLO_H


class Ejemplo {
private:
    int three = 3;
    int four = 4;
    int five = 5;

public:
    int getThree() const;

    int getFour() const;

    int getFive() const;

    bool exists() { return true; }
};


#endif //TP_FINAL_EJEMPLO_H
