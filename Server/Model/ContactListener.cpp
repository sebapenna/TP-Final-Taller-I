#include <iostream>
#include "ContactListener.h"
#include "constants.h"
#include "Chell.h"
#include <Server/Model/Collidable.h>
#include <Server/Model/Obstacles/Gate.h>

ContactListener::ContactListener(b2World *world) {
    _world = world;
}

void ContactListener::BeginContact(b2Contact *contact) {
    auto fix1 = contact->GetFixtureA();
    auto fix2 = contact->GetFixtureB();
    if (fix1 && fix2) {
        auto coll1 = (Collidable*) contact->GetFixtureA()->GetBody()->GetUserData();
        auto coll2 = (Collidable*) contact->GetFixtureB()->GetBody()->GetUserData();
        coll1->collideWith(coll2);
        coll2->collideWith(coll1);
    }
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
    auto cname1 = coll1->classId();
    auto cname2 = coll2->classId();
    if (cname1 == ENERGY_BARRIER && (cname2 == ENERGY_BALL || cname2 == CHELL)) {
        contact->SetEnabled(false);
    } else if ((cname2 == ENERGY_BARRIER) && (cname1 == ENERGY_BALL || cname1 == CHELL)) {
        contact->SetEnabled(false);
    } else if ((cname1 == ENERGY_BALL && cname2 == ENERGY_BALL) ||
            (cname2 == ENERGY_BALL && cname1 == ENERGY_BALL)) {
        contact->SetEnabled(false);
    } else if ((cname1 == ENERGY_BALL || cname1 == ROCK) && cname2 == GATE) {
        auto gate = (Gate*) coll2;
        if (gate->isOpen())
            contact->SetEnabled(false); // Bola energia pasa compuerta abierta
    } else if ((cname2 == ENERGY_BALL || cname2 == ROCK) && cname1 == GATE) {
        auto gate = (Gate*) coll1;
        if (gate->isOpen())
            contact->SetEnabled(false); // Bola energia pasa compuerta abierta
    } else if (cname1 == ROCK && cname2 == ENERGY_BALL) {
        coll2->collideWith(coll1);
        contact->SetEnabled(false); // Evito que roca se mueva por el choque
    } else if (cname2 == ROCK && cname1 == ENERGY_BALL) {
        coll1->collideWith(coll2);
        contact->SetEnabled(false);
    } else if (cname1 == ROCK && cname2 == CHELL) {
        coll2->collideWith(coll1);
    } else if (cname1 == CHELL && cname2 == ROCK) {
        coll1->collideWith(coll2);
    } else if (cname1 == CHELL && cname2 == GATE) {
        auto gate = (Gate*) coll2;
        if (gate->isOpen())
            contact->SetEnabled(false);
        else
            coll1->collideWith(coll2);
    } else if (cname2 == CHELL && cname1 == GATE) {
        auto gate = (Gate*) coll1;
        if (gate->isOpen())
            contact->SetEnabled(false);
        else
            coll2->collideWith(coll1);
    } else if (cname1 == CHELL && cname2 == CHELL) {
        contact->SetEnabled(false);
    } else if ((cname1 == CHELL && cname2 == ENERGY_BARRIER) ||
    (cname1 == ENERGY_BARRIER && cname2 == CHELL)) {
        contact->SetEnabled(false);
    } else if (cname1 == CHELL && (cname2 == PORTAL/* || cname2 == METAL_DIAGONAL_BLOCK*/)) {
        auto chell = (Chell*) coll1;    // Si portal en bloque diagonal evito deteccion contacto
        if (chell->ifTeleportedSetDone()) // Contacto se debe a que es punto de salida
            contact->SetEnabled(false); // Ignoro contacto con portal salida
    } else if (cname2 == CHELL && (cname1 == PORTAL /*|| cname1 == METAL_DIAGONAL_BLOCK*/)) {
        auto chell = (Chell*) coll2;    // Si portal en bloque diagonal evito deteccion contacto
        if (chell->ifTeleportedSetDone())  // Contacto se debe a que es punto de salida
            contact->SetEnabled(false); // Ignoro contacto con portal salida
    }
}

// todo: refactor de los if/else