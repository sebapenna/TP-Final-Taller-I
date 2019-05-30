#ifndef TP_FINAL_BOTON_H
#define TP_FINAL_BOTON_H

#include "Box2D/Box2D.h"

class Button {
private:
    b2Body *_body;
    const size_t _id;
    uint8_t _state;
    bool _activated;

public:
    Button(const size_t id, b2Body *body);

    void activate();

    void deactivate();

    bool isActivated();

    void updateState();

    const size_t getId() const;
};


#endif //TP_FINAL_BOTON_H
