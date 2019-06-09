#ifndef PORTAL_BLOQUE_ROCA_H
#define PORTAL_BLOQUE_ROCA_H

#include <cstdint>
#include <Server/Collidable.h>

class RockBlock: public Collidable {
public:
    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;
};


#endif //PORTAL_BLOQUE_ROCA_H
