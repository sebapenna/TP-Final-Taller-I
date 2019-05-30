#ifndef PORTAL_TESTBUTTON_H
#define PORTAL_TESTBUTTON_H

#include <cppunit/extensions/HelperMacros.h>
#include "src/World.h"
#include "../src/constants.h"
#include "../src/exceptions.h"

using std::cout;
using std::endl;

class TestButton : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestButton);
        CPPUNIT_TEST( testCreate );
        CPPUNIT_TEST( testActivateOneButton );
        CPPUNIT_TEST( testActivateMoreThanOneButton );
        CPPUNIT_TEST( testActivateAndDeactivate );
        CPPUNIT_TEST( testActivateDeactivateAndReactivate );
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    Button *button1;
    Button *button2;
    size_t width = 100;
    size_t height = 200;
    float button1_x = 0, button1_y = 2, button2_x = 6, button2_y = 2;

public:
    void setUp() {
        world = new World(width, height);
        world->createRockBlock(100, 4, 0, -2); // Piso
        world->createButton(0, button1_x, button1_y);
        world->createButton(1, button2_x, button2_y);
        auto button_vector = world->getButtons();
        button1 = button_vector[0];
        button2 = button_vector[1];
    }

    void tearDown() {
        delete world;
    }
    
    void testCreate() {
        cout << endl << endl << "TEST BUTTON";
        cout << endl << "TEST crear correctamente: ";
        auto button_vector = world->getButtons();
        CPPUNIT_ASSERT_EQUAL((size_t) 2, button_vector.size());
        CPPUNIT_ASSERT(!button1->isActivated());
        CPPUNIT_ASSERT(!button2->isActivated());
        CPPUNIT_ASSERT_EQUAL((size_t) 2, button_vector.size());
        cout << "OK";
    }

    void testActivateOneButton() {
        cout << endl << "TEST activar un solo boton: ";
        button1->activate();
        CPPUNIT_ASSERT(!button1->isActivated());    // Se activa luego de step
        for (int i = 0; i < STEP_ITERATIONS; i++)   // Activo boton 1
            world->step();
        CPPUNIT_ASSERT(button1->isActivated());
        cout << "OK";
    }

    void testActivateMoreThanOneButton() {
        cout << endl << "TEST activar mas de uno: ";
        button1->activate();
        for (int i = 0; i < STEP_ITERATIONS; i++)   // Activo boton 1
            world->step();
        CPPUNIT_ASSERT(button1->isActivated());
        CPPUNIT_ASSERT(!button2->isActivated());
        button2->activate();
        CPPUNIT_ASSERT(!button2->isActivated());    // Se activa luego de step
        for (int i = 0; i < STEP_ITERATIONS; i++)   // Activo boton 2
            world->step();
        CPPUNIT_ASSERT(button1->isActivated());
        CPPUNIT_ASSERT(button2->isActivated());
        cout << "OK";
    }

    void testActivateAndDeactivate() {
        cout << endl << "TEST activar y desactivar: ";
        button1->activate();
        button2->activate();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        button1->deactivate();
        button2->deactivate();
        CPPUNIT_ASSERT(button1->isActivated()); // Se desactivan luego de step
        CPPUNIT_ASSERT(button2->isActivated());
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(!button1->isActivated());
        CPPUNIT_ASSERT(!button2->isActivated());
        cout << "OK";
    }

    void testActivateDeactivateAndReactivate() {
        cout << endl << "TEST activar, desactivar y reactivar: ";
        button1->activate();
        button2->activate();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        button1->deactivate();
        button2->deactivate();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        button1->activate();
        button2->activate();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(button1->isActivated());
        CPPUNIT_ASSERT(button2->isActivated());
        cout << "OK";
    }
};
#endif //PORTAL_TESTBUTTON_H
