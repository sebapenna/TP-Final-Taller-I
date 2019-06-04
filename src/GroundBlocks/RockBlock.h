#ifndef PORTAL_BLOQUE_ROCA_H
#define PORTAL_BLOQUE_ROCA_H

#include <cstdint>
#include <src/Collidable.h>

class RockBlock: public Collidable {
public:
    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;
};


#endif //PORTAL_BLOQUE_ROCA_H
