#ifndef PORTAL_TESTGATE_H
#define PORTAL_TESTGATE_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <Common/exceptions.h>

using std::cout;
using std::endl;

class TestGate : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestGate);
        CPPUNIT_TEST(testCreate);
        CPPUNIT_TEST(testOpen);
        CPPUNIT_TEST(testClose);
        CPPUNIT_TEST(testOpenMoreThanOne);
        CPPUNIT_TEST(testCloseMoreThanOne);
        CPPUNIT_TEST(testGateAddedToUpdateVectorAfterOpening);
        CPPUNIT_TEST(testGateAddedToUpdateVectorAfterClosing);
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    Button *button1;
    Button *button2;
    Gate *gate1;
    Gate *gate2;
    EnergyReceiver *e_recvr1;
    EnergyReceiver *e_recvr2;
    size_t width = 100, height = 200;
    float button1_x = 0, button1_y = 2, button2_x = 6, button2_y = 2;
    float e_recvr1_x = 40, e_recvr1_y = 2, e_recvr2_x = 50, e_recvr2_y = 2;
    float gate1_x = -10, gate1_y = 4, gate2_x = -20, gate2_y = 4;
    int init_n_bodies;

public:
    void setUp() {
        world = new World(width, height);
        world->createRockBlock(100, 4, 0, -2); // Piso
        world->createButton(button1_x, button1_y);
        world->createButton(button2_x, button2_y);
        button1 = world->getButton(0);
        button2 = world->getButton(1);
        world->createEnergyReceiver(e_recvr1_x, e_recvr1_y);
        world->createEnergyReceiver(e_recvr2_x, e_recvr2_y);
        e_recvr1 = world->getEnergyReceiver(0);
        e_recvr2 = world->getEnergyReceiver(1);
        world->createGate(gate1_x, gate1_y, {0, 1}, {1});
        world->createGate(gate2_x, gate2_y, {0}, {0, 1});
        init_n_bodies = 7;
        gate1 = world->getGate(0);
        gate2 = world->getGate(1);
    }

    void tearDown() {
        delete world;
    }

    void testCreate() {
        cout << endl << endl << "TEST GATE";
        cout << endl << "TEST crear correctamente: ";
        CPPUNIT_ASSERT_EQUAL(init_n_bodies, world->getWorld()->GetBodyCount());
        CPPUNIT_ASSERT(!gate1->isOpen());
        CPPUNIT_ASSERT(!gate2->isOpen());
        cout << "OK";
    }

    void testOpen() {
        cout << endl << "TEST abrir: ";
        button1->activate();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        button2->activate();
        CPPUNIT_ASSERT(!gate1->isOpen());   // Restan condiciones para abrir
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        e_recvr2->activate();
        CPPUNIT_ASSERT(!gate1->isOpen());   // Resta activar un receptor
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(gate1->isOpen());
        cout << "OK";
    }

    void testClose() {
        cout << endl << "TEST cerrar cuando una condicion se desactiva: ";
        button1->activate();
        button2->activate();
        e_recvr2->activate();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        button1->deactivate();  // Desactivo boton 1
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(!gate1->isOpen());
        button1->activate();  // Reactivo boton 1
        button2->deactivate();  // Desactivo boton 2
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(!gate1->isOpen());
        button1->deactivate();  // Desactivo boton 1 (ambos desactivados)
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(!gate1->isOpen());
        cout << "OK";
    }

    void testOpenMoreThanOne() {
        cout << endl << "TEST abrir mas de una: ";
        button1->activate();
        button2->activate();
        e_recvr2->activate();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(gate1->isOpen());
        CPPUNIT_ASSERT(!gate2->isOpen());   // Resta activar un receptor energia
        e_recvr1->activate();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(gate1->isOpen());
        CPPUNIT_ASSERT(gate2->isOpen());
        cout << "OK";
    }

    void testCloseMoreThanOne() {
        cout << endl << "TEST cerrar mas de una: ";
        button1->activate();
        button2->activate();
        e_recvr1->activate();
        e_recvr2->activate();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(gate1->isOpen());
        CPPUNIT_ASSERT(gate2->isOpen());
        button2->deactivate();  // Desactivo boton necesario para gate1
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(!gate1->isOpen());
        CPPUNIT_ASSERT(gate2->isOpen());
        button1->deactivate();  // Desactivo boton neceario para gate2
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(!gate1->isOpen());
        CPPUNIT_ASSERT(!gate2->isOpen());
        cout << "OK";
    }

    void testGateAddedToUpdateVectorAfterOpening() {
        cout << endl << "TEST verificar que se agrega a vector de objetos actualizados luego de "
                        "abrir: ";
        button1->activate();
        button2->activate();
        e_recvr1->activate();
        e_recvr2->activate();
        world->step();
        // Se actualizan botones, receivers y gates
        CPPUNIT_ASSERT_EQUAL((size_t) 6, world->getObjectsToUpdate().size());
        auto updated_vec = world->getObjectsToUpdate();
        size_t id = 0;
        for (auto &updated : updated_vec) {
            if (updated->getClassId() == GATE){
                auto updated_gate = (Gate*) updated;
                CPPUNIT_ASSERT_EQUAL(id, updated_gate->getId());
                CPPUNIT_ASSERT(updated_gate->isOpen());
                ++id;
            }
        }
        cout << "OK";
    }

    void testGateAddedToUpdateVectorAfterClosing() {
        cout << endl << "TEST verificar que se agrega a vector de objetos actualizados luego de "
                        "abrir: ";
        button1->activate();
        button2->activate();
        e_recvr1->activate();
        e_recvr2->activate();
        world->step();
        button1->deactivate();
        button2->deactivate();
        world->step();
        // Se actualizan botones y gates
        CPPUNIT_ASSERT_EQUAL((size_t) 4, world->getObjectsToUpdate().size());
        auto updated_vec = world->getObjectsToUpdate();
        size_t id = 0;
        for (auto &updated : updated_vec) {
            if (updated->getClassId() == GATE){
                auto updated_gate = (Gate*) updated;
                CPPUNIT_ASSERT_EQUAL(id, updated_gate->getId());
                CPPUNIT_ASSERT(!updated_gate->isOpen());
                ++id;
            }
        }
        cout << "OK";
    }
};
    
#endif //PORTAL_TESTGATE_H
