#ifndef PORTAL_BLOQUE_METAL_H
#define PORTAL_BLOQUE_METAL_H

#include <cstdint>
#include <src/Collidable.h>

class MetalBlock: public Collidable {
public:
    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;
};


#endif //PORTAL_BLOQUE_METAL_H
