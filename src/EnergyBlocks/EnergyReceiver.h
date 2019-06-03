#ifndef TP_FINAL_RECEPTOR_ENERGIA_H
#define TP_FINAL_RECEPTOR_ENERGIA_H

#include <src/Collidable.h>
#include <src/constants.h>

class EnergyReceiver: Collidable {
private:

    uint8_t _state = NOT_ACTIVATED;
    bool _activated = false;

public:
    void activate();

    bool isActivated();

    void updateState();

    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

private:
    void endCollitionWith(Collidable *other) override;
};


#endif //TP_FINAL_RECEPTOR_ENERGIA_H
