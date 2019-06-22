#ifndef PORTAL_TESTENERGYRECEIVER_H
#define PORTAL_TESTENERGYRECEIVER_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <Common/exceptions.h>
#include <Server/CollidableData/Data/EnergyReceiverData.h>

using std::cout;
using std::endl;
using std::make_shared;

class TestEnergyReceiver : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestEnergyReceiver);
        CPPUNIT_TEST( testCreate );
        CPPUNIT_TEST( testActivate );
        CPPUNIT_TEST( testActivateMoreThanOne );
    CPPUNIT_TEST_SUITE_END();

private:
    std::shared_ptr<Configuration> ptr;
    Configuration *config;
    World *world;
    EnergyReceiver *e_recvr1;
    EnergyReceiver *e_recvr2;
    size_t width = 100, height = 200;
    float e_recvr1_x = 0, e_recvr1_y = 2, e_recvr2_x = 6, e_recvr2_y = 2;
    int init_n_bodies;

public:
    void setUp() {
        ptr = make_shared<Configuration>();
config = ptr.get();
        world = new World(width, height, ptr);
        auto data = make_shared<RockBlockData>(100, 4, 0, -2); // Piso
        world->createCollidable(data);
        auto data2 = make_shared<EnergyReceiverData>(0, e_recvr1_x, e_recvr1_y);
        world->createCollidable(data2);
        auto data3 = make_shared<EnergyReceiverData>(0, e_recvr2_x, e_recvr2_y);
        world->createCollidable(data3);
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
        for (int i = 0; i < config->getFps(); i++)   // Activo receptor 1
            world->step();
        CPPUNIT_ASSERT(e_recvr1->isActivated());
        cout << "OK";
    }

    void testActivateMoreThanOne() {
        cout << endl << "TEST activar mas de uno: ";
        e_recvr1->activate();
        for (int i = 0; i < config->getFps(); i++)   // Activo receptor 1
            world->step();
        CPPUNIT_ASSERT(e_recvr1->isActivated());
        CPPUNIT_ASSERT(!e_recvr2->isActivated());
        e_recvr2->activate();
        CPPUNIT_ASSERT(!e_recvr2->isActivated());
        for (int i = 0; i < config->getFps(); i++)   // Activo receptor 2
            world->step();
        CPPUNIT_ASSERT(e_recvr1->isActivated());
        CPPUNIT_ASSERT(e_recvr2->isActivated());
        cout << "OK";
    }
};

#endif //PORTAL_TESTENERGYRECEIVER_H
