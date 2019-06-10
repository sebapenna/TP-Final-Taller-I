#ifndef PORTAL_ACID_H
#define PORTAL_ACID_H

#include <Server/Model/Collidable.h>

class Acid: public Collidable {
public:
    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;
};


#endif //PORTAL_ACID_H
