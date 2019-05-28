#include <iostream>
#include "ContactListener.h"

ContactListener::ContactListener(b2World *world) {
    _world = world;
}

void ContactListener::beginContact(b2Contact *contact) {
    std::cout << "CONTACTO" << std::endl;
    auto *fixture_1 = contact->GetFixtureA();
    auto *fixture_2 = contact->GetFixtureB();
    std::cout << fixture_1->GetBody()->GetType() << " contacto a " <<
    fixture_2->GetBody()->GetType() << std::endl;
}
