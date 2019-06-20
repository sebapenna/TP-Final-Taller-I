#ifndef TP_FINAL_PORTAL_H
#define TP_FINAL_PORTAL_H


#include <cstdint>
#include <Server/Model/Collidable.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>

class Portal: public Collidable {
private:
    b2Body *_body;
    b2Vec2  _normal;
    const int16_t _color;
    const size_t _id;
    const float _width, _height;
    Portal *_exit_portal = nullptr;   // Portal por el que tiene que salir

public:
    Portal(const size_t&  id, b2Body *body, const b2Vec2 normal, const int16_t color,
            const float& width, const float& height);

    ~Portal() override;

    void collideWith(Collidable *other) override;

    const uint8_t classId() override;

    bool actedDuringStep() override;

    void endCollitionWith(Collidable *other) override;

    // Obtiene la inclinacion del portal en base a la normal
    const int16_t tilt();

    const int16_t colour() const;

    const size_t id() const;

    b2Body *getBody() const;

    const float getWidth() const;

    const float getHeight() const;

    const b2Vec2 &normal() const;

    void setExitPortal(Portal *other);

    // Retorna el portal de salida, nullptr en caso de que nunca haya sido asignado
    Portal *exitPortal() const;

    const float x() override;

    const float y() override;

    const float width() override;

    const float height() override;
};


#endif //TP_FINAL_PORTAL_H
