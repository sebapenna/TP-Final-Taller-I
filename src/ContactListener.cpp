#include <iostream>
#include "ContactListener.h"
#include "constants.h"
#include <src/Collidable.h>
#include <src/Obstacles/Gate.h>

ContactListener::ContactListener(b2World *world) {
    _world = world;
}

void ContactListener::BeginContact(b2Contact *contact) {
    auto coll1 = (Collidable*) contact->GetFixtureA()->GetBody()->GetUserData();
    auto coll2 = (Collidable*) contact->GetFixtureB()->GetBody()->GetUserData();
    coll1->collideWith(coll2);
    coll2->collideWith(coll1);
}

void ContactListener::EndContact(b2Contact *contact) {
    auto coll1 = (Collidable*) contact->GetFixtureA()->GetBody()->GetUserData();
    auto coll2 = (Collidable*) contact->GetFixtureB()->GetBody()->GetUserData();
    coll1->endCollitionWith(coll2);
    coll2->endCollitionWith(coll1);
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManif) {
    auto coll1 = (Collidable*) contact->GetFixtureA()->GetBody()->GetUserData();
    auto coll2 = (Collidable*) contact->GetFixtureB()->GetBody()->GetUserData();
    auto cname1 = coll1->getClassName();
    auto cname2 = coll2->getClassName();
    if (cname1 == ENERGY_BARRIER & (cname2 == ENERGY_BALL || cname2 == CHELL)) {
        contact->SetEnabled(false);
    } else if ((cname2 == ENERGY_BARRIER) &&
                (cname1 == ENERGY_BALL || cname1 == CHELL)) {
        contact->SetEnabled(false);
    } else if ((cname1 == ENERGY_BALL && cname2 == ENERGY_BALL) ||
            (cname2 == ENERGY_BALL && cname1 == ENERGY_BALL)) {
        contact->SetEnabled(false);
    } else if (cname1 == ENERGY_BALL && cname2 == GATE) {
        auto gate = (Gate*) coll2;
        if (gate->isOpen())
            contact->SetEnabled(false); // Bola energia pasa compuerta abierta
    } else if (cname2 == ENERGY_BALL && cname1 == GATE) {
        auto gate = (Gate*) coll1;
        if (gate->isOpen())
            contact->SetEnabled(false); // Bola energia pasa compuerta abierta
    }
}
