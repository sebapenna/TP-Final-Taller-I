#include <iostream>
#include "ContactListener.h"
#include "constants.h"
#include <src/Collidable.h>

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
    auto class_name1 = coll1->getClassName();
    auto class_name2 = coll2->getClassName();
    if ((class_name1 == ENERGY_BARRIER && class_name2 != ROCK) ||
        (class_name2 == ENERGY_BARRIER && class_name1 != ROCK))
        contact->SetEnabled(false); // Contacto de barrera no es con roca
}
