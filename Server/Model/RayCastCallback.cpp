#include "RayCastCallback.h"

RayCastCallback::RayCastCallback() {
    m_fixture = nullptr;
}

float32
RayCastCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal,
                               float32 fraction) {
    m_fixture = fixture;
    m_point = point;
    m_normal = normal;
    m_fraction = fraction;
    return fraction;
}
