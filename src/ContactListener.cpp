#include <iostream>
#include "ContactListener.h"
#include "Chell.h"
#include <typeinfo>

ContactListener::ContactListener(b2World *world) {
    _world = world;
}

void ContactListener::BeginContact(b2Contact *contact) {
    auto *fixture_1 = contact->GetFixtureA();
    auto *fixture_2 = contact->GetFixtureB();
//    auto *aux = fixture_1->GetUserData();
//    std::cout << std::endl<< "aux: "<< typeid(*aux).name();
    if (typeid(fixture_1->GetUserData()) == typeid(Chell))
        std::cout << std::endl <<"CONTACTO CHELL"<< std::endl;
    if (typeid(fixture_2->GetUserData()) == typeid(Chell))
        std::cout << std::endl <<"CONTACTO CHELL"<< std::endl;
//    std::cout << typeid(fixture_1->GetUserData()).name() << " contacto a " <<
//    typeid(fixture_2->GetUserData()).name() << std::endl;
}