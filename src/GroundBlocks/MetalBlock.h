#ifndef TP_FINAL_BLOQUE_METAL_H
#define TP_FINAL_BLOQUE_METAL_H

#include <cstdint>
#include <src/Collidable.h>

class MetalBlock: Collidable {
public:
    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

private:
    void endCollitionWith(Collidable *other) override;
};


#endif //TP_FINAL_BLOQUE_METAL_H
