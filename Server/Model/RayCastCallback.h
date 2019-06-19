#ifndef PORTAL_RAYCASTCALLBACK_H
#define PORTAL_RAYCASTCALLBACK_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Box2D.h>

class RayCastCallback : public b2RayCastCallback {
public:
    RayCastCallback();

    // Se encarga de comprobar contra que cuerpo chocho, en caso de ser una chell o una gate
    // abierta continuara el disparo, de lo contrario retornara el primer cuerpo contra el que
    // colisiona el disparo.
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
            float32 fraction) override;


    b2Fixture* m_fixture;
    b2Vec2 m_point;
    b2Vec2 m_normal;
    float32 m_fraction;
};


#endif //PORTAL_RAYCASTCALLBACK_H
