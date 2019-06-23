#ifndef PORTAL_ROCA_H
#define PORTAL_ROCA_H

#include <Box2D/Box2D.h>
#include <Server/Model/Collidable.h>
#include <Server/Model/Shots/Portal.h>
#include <Server/Model/Chell.h>

class Rock: public Collidable {
private:
    b2Body *_body;
    const size_t _id;
    float _previous_x, _previous_y;
    bool _dead = false;
    const float _width, _height;
    bool _teleported = false;
    Portal *_portal_to_use = nullptr;
    float _density;

public:
    explicit Rock(const size_t &id, b2Body *body, const float& width, const float& height);
    Chell *_lifter = nullptr;   // Chell que la esta cargando

    ~Rock() override;

    float velocityY();

    b2Body *getBody() const override;

    bool isDead(const float& time_step) override;

    const size_t id() const;

    void teletransport(float x, float y);

    const uint8_t classId() override;

    void collideWith(Collidable *other) override;

    void endCollitionWith(Collidable *other) override;

    bool actedDuringStep() override;

    const float x() override;

    const float y() override;

    const float width() override;

    const float height() override;

    void step(const float &time_step) override;

    void teleport(float x, float y);

    // Indica que portal atravesara la chell, por lo tanto roca debe hacer lo mismo
    void setPortalToUse(Portal *portal);

    bool ifTeleportedSetDone();

    void setLifter(Chell *chell);
    void removeLifter();
};


#endif //PORTAL_ROCA_H
