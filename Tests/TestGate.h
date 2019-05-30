#ifndef PORTAL_TESTGATE_H
#define PORTAL_TESTGATE_H

#include <cppunit/extensions/HelperMacros.h>
#include "src/World.h"
#include "src/constants.h"
#include "src/exceptions.h"

using std::cout;
using std::endl;

class TestGate : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestGate);
        CPPUNIT_TEST(testCreate);
        CPPUNIT_TEST(testOpen);
        CPPUNIT_TEST(testClose);
        CPPUNIT_TEST(testOpenMoreThanOne);
        CPPUNIT_TEST(testCloseMoreThanOne);
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

public:
    void setUp() {
        world = new World(width, height);
        world->createRockBlock(100, 4, 0, -2); // Piso
        world->createButton(0, button1_x, button1_y);
        world->createButton(1, button2_x, button2_y);
        auto button_vector = world->getButtons();
        button1 = button_vector[0];
        button2 = button_vector[1];
        world->createEnergyReceiver(0, e_recvr1_x, e_recvr1_y);
        world->createEnergyReceiver(1, e_recvr2_x, e_recvr2_y);
        auto e_recvr_vector = world->getEnergyReceivers();
        e_recvr1 = e_recvr_vector[0];
        e_recvr2 = e_recvr_vector[1];
        world->createGate(0, gate1_x, gate1_y, {0, 1}, {1});
        world->createGate(1, gate2_x, gate2_y, {0}, {0, 1});
        auto gate_vector = world->getGates();
        gate1 = gate_vector[0];
        gate2 = gate_vector[1];
    }

    void tearDown() {
        delete world;
    }

    void testCreate() {
        cout << endl << endl << "TEST GATE";
        cout << endl << "TEST crear correctamente: ";
        auto gate_vector = world->getGates();
        CPPUNIT_ASSERT_EQUAL((size_t) 2, gate_vector.size());
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
};
    
#endif //PORTAL_TESTGATE_H
