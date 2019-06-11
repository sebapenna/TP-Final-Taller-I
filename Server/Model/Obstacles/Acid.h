#ifndef PORTAL_ACID_H
#define PORTAL_ACID_H

#include <Server/Model/Collidable.h>

class Acid: public Collidable {
private:
    const float _x, _y;
public:
    Acid(const float& x, const float& y);

    const uint8_t getClassId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float getX() const;

    const float getY() const;
};


#endif //PORTAL_ACID_H
