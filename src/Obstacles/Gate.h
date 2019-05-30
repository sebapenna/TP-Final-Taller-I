#ifndef TP_FINAL_COMPUERTA_H
#define TP_FINAL_COMPUERTA_H

class Gate {
private:
    bool _open;

public:
    Gate();

    void open();

    void close();

    bool isOpen();

    Gate& operator=(Gate &&other);
};


#endif //TP_FINAL_COMPUERTA_H
