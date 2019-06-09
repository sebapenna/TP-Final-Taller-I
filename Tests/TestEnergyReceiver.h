#ifndef PORTAL_TESTENERGYRECEIVER_H
#define PORTAL_TESTENERGYRECEIVER_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/World.h"
#include "Server/constants.h"
#include <Common/exceptions.h>

using std::cout;
using std::endl;

class TestEnergyReceiver : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestEnergyReceiver);
        CPPUNIT_TEST( testCreate );
        CPPUNIT_TEST( testActivate );
        CPPUNIT_TEST( testActivateMoreThanOne );
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    EnergyReceiver *e_recvr1;
    EnergyReceiver *e_recvr2;
    size_t width = 100, height = 200;
    float e_recvr1_x = 0, e_recvr1_y = 2, e_recvr2_x = 6, e_recvr2_y = 2;
    int init_n_bodies;

public:
    void setUp() {
        world = new World(width, height);
        world->createRockBlock(100, 4, 0, -2); // Piso
        world->createEnergyReceiver(0, e_recvr1_x, e_recvr1_y);
        world->createEnergyReceiver(1, e_recvr2_x, e_recvr2_y);
        init_n_bodies = 3;
        e_recvr1 = world->getEnergyReceiver(0);
        e_recvr2 = world->getEnergyReceiver(1);
    }

    void tearDown() {
        delete world;
    }

    void testCreate() {
        cout << endl << endl << "TEST ENERGY RECEIVER";
        cout << endl << "TEST crear correctamente :";
        CPPUNIT_ASSERT_EQUAL(init_n_bodies, world->getWorld()->GetBodyCount());
        CPPUNIT_ASSERT(!e_recvr1->isActivated());
        CPPUNIT_ASSERT(!e_recvr2->isActivated());
        cout << "OK";
    }

    void testActivate() {
        cout << endl << "TEST activar: ";
        e_recvr1->activate();
        CPPUNIT_ASSERT(!e_recvr1->isActivated()); // Se activa luego de step
        for (int i = 0; i < STEP_ITERATIONS; i++)   // Activo receptor 1
            world->step();
        CPPUNIT_ASSERT(e_recvr1->isActivated());
        cout << "OK";
    }

    void testActivateMoreThanOne() {
        cout << endl << "TEST activar mas de uno: ";
        e_recvr1->activate();
        for (int i = 0; i < STEP_ITERATIONS; i++)   // Activo receptor 1
            world->step();
        CPPUNIT_ASSERT(e_recvr1->isActivated());
        CPPUNIT_ASSERT(!e_recvr2->isActivated());
        e_recvr2->activate();
        CPPUNIT_ASSERT(!e_recvr2->isActivated());
        for (int i = 0; i < STEP_ITERATIONS; i++)   // Activo receptor 2
            world->step();
        CPPUNIT_ASSERT(e_recvr1->isActivated());
        CPPUNIT_ASSERT(e_recvr2->isActivated());
        cout << "OK";
    }
};

#endif //PORTAL_TESTENERGYRECEIVER_H
