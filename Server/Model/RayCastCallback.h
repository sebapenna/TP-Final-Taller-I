#ifndef PORTAL_RAYCASTCALLBACK_H
#define PORTAL_RAYCASTCALLBACK_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Common/b2Math.h>

class RayCastCallback : public b2RayCastCallback {
public:
    RayCastCallback();

    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
            float32 fraction);


    b2Fixture* m_fixture;
    b2Vec2 m_point;
    b2Vec2 m_normal;
    float32 m_fraction;
};


#endif //PORTAL_RAYCASTCALLBACK_H
