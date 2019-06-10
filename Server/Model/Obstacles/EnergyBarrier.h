#ifndef PORTAL_ENERGYBARRIER_H
#define PORTAL_ENERGYBARRIER_H

#include <Server/Model/Collidable.h>

class EnergyBarrier: public Collidable {
public:
    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;
};


#endif //PORTAL_ENERGYBARRIER_H
