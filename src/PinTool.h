#ifndef PORTAL_PINTOOL_H
#define PORTAL_PINTOOL_H

#include <src/Collidable.h>

class PinTool: public Collidable {
public:
    const std::string getClassName() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;
};


#endif //PORTAL_PINTOOL_H
