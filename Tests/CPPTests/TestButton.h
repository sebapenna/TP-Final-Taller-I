#ifndef PORTAL_TESTBUTTON_H
#define PORTAL_TESTBUTTON_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <Common/exceptions.h>

using std::cout;
using std::endl;

class TestButton : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestButton);
        CPPUNIT_TEST( testCreate );
        CPPUNIT_TEST( testActivateOneButton );
        CPPUNIT_TEST( testActivateMoreThanOneButton );
        CPPUNIT_TEST( testActivateAndDeactivate );
        CPPUNIT_TEST( testActivateDeactivateAndReactivate );
        CPPUNIT_TEST( testActivateCollitionWithRock );
        CPPUNIT_TEST( testDeactivateEndContactWithRock );
        CPPUNIT_TEST( testActivateContactWithChell );
        CPPUNIT_TEST( testActivateAndDeactivateContactWithChell );
        CPPUNIT_TEST( testAddedToUpdateVectorAfterActivating );
        CPPUNIT_TEST( testAddedToUpdateVectorAfterDeactivating );
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    Button *button1;
    Button *button2;
    size_t width = 100;
    size_t height = 200;
    float button1_x = 0, button1_y = 2, button2_x = 6, button2_y = 2;
    int init_n_bodies;  // Cantidad de bodies al inicio

public:
    void setUp() {
        world = new World(width, height);
        world->createRockBlock(100, 4, 0, -2); // Piso
        world->createButton(button1_x, button1_y);
        world->createButton(button2_x, button2_y);
        init_n_bodies = 3;
        button1 = world->getButton(0);
        button2 = world->getButton(1);
    }

    void tearDown() {
        delete world;
    }
    
    void testCreate() {
        cout << endl << endl << "TEST BUTTON";
        cout << endl << "TEST crear correctamente: ";
        CPPUNIT_ASSERT_EQUAL(init_n_bodies, world->getWorld()->GetBodyCount());
        CPPUNIT_ASSERT(!button1->isActivated());
        CPPUNIT_ASSERT(!button2->isActivated());
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

    void testActivateCollitionWithRock() {
        cout << endl << "TEST activar tras contacto con roca: ";
        // Hago que roca caiga sobre el boton
        float rock_x = button1_x;
        float dist_to_rock = BUTTON_HALF_HEIGHT + ROCK_HALF_LEN;
        float rock_y = button1_y + dist_to_rock + 2;
        world->createRock(rock_x, rock_y);
        CPPUNIT_ASSERT(!button1->isActivated());
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(button1->isActivated());
        auto rock = world->getRock(0);
        float diff_x = abs(button1_x - rock->x());
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x); // Verifico posicion de la roca
        cout << "OK";
    }

    void testDeactivateEndContactWithRock() {
        cout << endl << "TEST activar tras contacto con roca y descativar al "
                        "finalizar: ";
        // Hago que roca caiga sobre el boton
        float rock_x = button1_x;
        float dist_to_rock = BUTTON_HALF_HEIGHT + ROCK_HALF_LEN;
        float rock_y = button1_y + dist_to_rock + 2;
        world->createRock(rock_x, rock_y);
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(button1->isActivated());
        auto rock = world->getRock(0);
        rock->teletransport(rock_x + 50, rock_y);   // Saco roca del boton
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(!button1->isActivated());
        cout << "OK";
    }

    void testActivateContactWithChell() {
        cout << endl << "TEST activar tras contacto con chell: ";
        float chell_x = button1_x;
        float dist_to_chell = BUTTON_HALF_HEIGHT + CHELL_HALF_HEIGHT;
        float chell_y = button1_y + dist_to_chell + 2;
        world->createChell(chell_x, chell_y);
        CPPUNIT_ASSERT(!button1->isActivated());
        for (int i = 0; i < 2 * STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(button1->isActivated());
        auto chell = world->getChell(0);
        float diff_x = abs(button1_x - chell->x());
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x); // Verifico posicion de la roca
        cout << "OK";
    }

    void testActivateAndDeactivateContactWithChell() {
        cout << endl << "TEST activar tras contacto con chell y desactivar "
                        "al finalizar: ";
        float dist_to_chell_y = BUTTON_HALF_HEIGHT + CHELL_HALF_HEIGHT;
        float dist_to_chell_x = BUTTON_HALF_HEIGHT + CHELL_HALF_WIDTH;
        float chell_x = button1_x - dist_to_chell_x - 2;
        float chell_y = button1_y + dist_to_chell_y + 2;
        world->createChell(chell_x, chell_y);
        auto chell = world->getChell(0);
        chell->move_right(); // Muevo chell para que pase por boton
        bool button_act = false;
        CPPUNIT_ASSERT(!button1->isActivated());
        for (int i = 0; i < 200; i++) {
            world->step();
            if (button1->isActivated())
                button_act = true;
        }
        CPPUNIT_ASSERT(button_act);    // Boton se activo en algun momento
        CPPUNIT_ASSERT(!button1->isActivated());    // Finalizo el contacto
        CPPUNIT_ASSERT_GREATER(button1_x, chell->x()); // Paso la roca
        cout << "OK";
    }

    void testAddedToUpdateVectorAfterActivating() {
        cout << endl << "TEST verificar que se agrega a vector de objetos actualizados luego de "
                        "activarse: ";
        button1->activate();
        world->step();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getObjectsToUpdate().size());
        auto update_button = (Button*) world->getObjectsToUpdate().at(0);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, update_button->id());
        CPPUNIT_ASSERT(update_button->isActivated());
        cout << "OK";
    }

    void testAddedToUpdateVectorAfterDeactivating() {
        cout << endl << "TEST verificar que se agrega a vector de objetos actualizados luego de "
                        "desactivarse: ";
        button2->activate();
        world->step();
        button2->deactivate();
        world->step();
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getObjectsToUpdate().size());
        auto update_button = (Button*) world->getObjectsToUpdate().at(0);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, update_button->id());
        CPPUNIT_ASSERT(!update_button->isActivated());
        cout << "OK";
    }
};

#endif //PORTAL_TESTBUTTON_H
