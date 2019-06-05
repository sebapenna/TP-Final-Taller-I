#ifndef PORTAL_COLLIDABLE_H
#define PORTAL_COLLIDABLE_H

#include <string>

class Collidable {
public:
    virtual const std::string getClassName() = 0;

    virtual void collideWith(Collidable *other) = 0;

    virtual void endCollitionWith(Collidable *other) = 0;
};

#endif //PORTAL_COLLIDABLE_H