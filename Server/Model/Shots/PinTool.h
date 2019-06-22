#ifndef PORTAL_PINTOOL_H
#define PORTAL_PINTOOL_H

#include <Server/Model/Collidable.h>
#include <Box2D/Box2D.h>

class PinTool: public Collidable {
private:
    b2Body * _body;
    const size_t _id;
    const float _width, _height;
    float _lifetime = 0, _max_lifetime;
    bool _dead = false, _previously_dead = false, _time_step;
    // Guardo id de chell a la cual pertenece, para poder eliminar cuando tiempo de vida acabada
    const size_t _owner_chell_id;

public:
    PinTool(const size_t& id, const size_t& chell_id, b2Body * body, const float& width, const
    float& height, const float& max_lifetime, const float& time_step);

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

    const size_t getOwnerChellId() const;
};


#endif //PORTAL_PINTOOL_H
