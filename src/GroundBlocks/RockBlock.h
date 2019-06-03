#ifndef TP_FINAL_BLOQUE_ROCA_H
#define TP_FINAL_BLOQUE_ROCA_H

#include <cstdint>
#include <src/Collidable.h>

class RockBlock: public Collidable {
public:
    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;
};


#endif //TP_FINAL_BLOQUE_ROCA_H
