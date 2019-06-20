#include <Server/Model/Obstacles/Gate.h>
#include "RayCastCallback.h"
#include "Collidable.h"
#include "constants.h"

RayCastCallback::RayCastCallback() {
    m_fixture = nullptr;
}

float32
RayCastCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal,
                               float32 fraction) {
    auto collidable = (Collidable*) fixture->GetBody()->GetUserData();
    if (collidable->classId() == CHELL)
        return 1;   // Retornar uno implica continuar con el disparo e ignorar chell
    if (collidable->classId() == GATE) {
        auto gate = (Gate*) collidable;
        if (gate->isOpen())
            return 1;   // Continua el disparo
    }
    m_fixture = fixture;
    m_point = point;
    m_normal = normal;
    m_fraction = fraction;
    return fraction;
}
