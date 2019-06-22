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
    bool _dead = false, _previously_dead = false;
    // Guardo id de chell a la cual pertenece, para poder eliminar cuando tiempo de vida acabada
    const size_t _owner_chell_id;

public:
    PinTool(const size_t& id, const size_t& chell_id, b2Body * body, const float& width, const
    float& height, const float& max_lifetime);

    ~PinTool() override;

    const uint8_t classId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float x() override;

    const float y() override;

    const float width() override;

    const float height() override;

    const size_t id() const;

    b2Body *getBody() const override;

    bool isDead(const float& time_step) override;

    const size_t getOwnerChellId() const;

    void step(const float &time_step) override;
};


#endif //PORTAL_PINTOOL_H
