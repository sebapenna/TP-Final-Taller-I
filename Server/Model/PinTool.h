#ifndef PORTAL_PINTOOL_H
#define PORTAL_PINTOOL_H

#include <Server/Model/Collidable.h>
#include <Box2D/Box2D.h>

class PinTool: public Collidable {
private:
    b2Body * _body;
    const size_t _id;
    const float _width, _height;
    float _lifetime = 0;
    bool _dead = false, _previously_dead = false;

public:
    PinTool(const size_t& id, b2Body * body, const float& width, const float& height);

    ~PinTool() override;

    void updateLifetime();

    const uint8_t classId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float x() override;

    const float y() override;

    const float width() override;

    const float height() override;

    const size_t id() const;

    b2Body *getBody() const;

    bool isDead();
};


#endif //PORTAL_PINTOOL_H
