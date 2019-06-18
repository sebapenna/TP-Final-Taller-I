#ifndef PORTAL_TESTCAKE_H
#define PORTAL_TESTCAKE_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <Common/exceptions.h>
#include <string>

using std::cout;
using std::endl;

class TestCake : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestCake);
        CPPUNIT_TEST(testChellReachCake);
        CPPUNIT_TEST(testOnlyOneChellReachCake);
        CPPUNIT_TEST(testAllChellsReachCake);
        CPPUNIT_TEST(testKillOnlyChellThatDidntReachCake);
        CPPUNIT_TEST(testDontKillWhenNotAllReachedCake);
        CPPUNIT_TEST(testDontKillWhenNoneReachedCake);
        CPPUNIT_TEST(testDontKillWhenAllReachedCake);
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    Chell *chell;
    size_t width = 100;
    size_t height = 200;
    float chell_init_x = 0, chell_init_y = 2;
    float cake_x = 10, cake_y = 2;

public:
    void setUp() {
        world = new World(width, height);
        world->createRockBlock(1000, 4, 0, -2);  // Piso
        world->createChell(chell_init_x, chell_init_y);
        world->createCake(cake_x, cake_y);
        chell = world->getChell(0);
    }

    void tearDown() {
        delete world;
    }

    void testChellReachCake() {
        cout << endl << endl << "TESTS CAKE";
        cout << endl << "TEST chell llega a cake: ";
        chell->move_right();
        bool reached_cake = false;
        for (int i = 0; i < STEP_ITERATIONS; i++) {
            world->step();
            if (world->allChellsOnCake())
                reached_cake = true;
        }
        CPPUNIT_ASSERT(reached_cake);
        cout << "OK";
    }

    void testOnlyOneChellReachCake() {
        cout << endl << "TEST solo una chell llega a cake: ";
        float chell2_x = chell_init_x - 20, chell2_y = chell_init_y;
        world->createChell(chell2_x, chell2_y);
        chell->move_right();
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(chell->reachedCake());
        CPPUNIT_ASSERT(!world->allChellsOnCake());
        cout << "OK";
    }

    void testAllChellsReachCake() {
        cout << endl << "TEST todas las chell llegan a cake: ";
        float chell2_x = chell_init_x - 20, chell2_y = chell_init_y;
        float chell3_x = chell_init_x - 30, chell3_y = chell_init_y;
        world->createChell(chell2_x, chell2_y);
        world->createChell(chell3_x, chell3_y);
        auto chell2 = world->getChell(1);
        auto chell3 = world->getChell(2);
        chell->move_right();
        chell2->move_right();
        chell3->move_right();
        for (int i = 0; i < 3 * STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(world->allChellsOnCake());
        cout << "OK";
    }

    void testKillOnlyChellThatDidntReachCake() {
        cout << endl << "TEST matar a unica chell que no llega a cake: ";
        float chell2_x = chell_init_x - 20, chell2_y = chell_init_y;
        float chell3_x = chell_init_x - 30, chell3_y = chell_init_y;
        world->createChell(chell2_x, chell2_y);
        world->createChell(chell3_x, chell3_y);
        auto chell2 = world->getChell(1);
        auto chell3 = world->getChell(2);
        chell->move_right();
        chell2->move_right();
        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < 3 * STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(!world->allChellsOnCake());
        CPPUNIT_ASSERT(world->killLastingChell());  // Se pudo eliminar chell restante
        world->step();  // Permito que se aplique 'asesinato'
        chell = world->getChell(0);
        chell2 = world->getChell(1);
        chell3 = world->getChell(2);
        // Verifico se elimino la chell correcta
        CPPUNIT_ASSERT(chell);
        CPPUNIT_ASSERT(chell2);
        CPPUNIT_ASSERT(!chell3);
        CPPUNIT_ASSERT_LESS(n_bodies, world->getWorld()->GetBodyCount());   // Chell ya no existe
        cout << "OK";
    }

    void testDontKillWhenNotAllReachedCake() {
        cout << endl << "TEST no matar cuando mas de una no llego a cake: ";
        float chell2_x = chell_init_x - 20, chell2_y = chell_init_y;
        float chell3_x = chell_init_x - 30, chell3_y = chell_init_y;
        world->createChell(chell2_x, chell2_y);
        world->createChell(chell3_x, chell3_y);
        chell->move_right();
        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < 3 * STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(!world->allChellsOnCake());
        CPPUNIT_ASSERT(!world->killLastingChell());  // // No se elimino
        world->step();  // Permito que se aplique posible 'asesinato'
        chell = world->getChell(0);
        auto chell2 = world->getChell(1);
        auto chell3 = world->getChell(2);
        // Verifico no se elimino
        CPPUNIT_ASSERT(chell);
        CPPUNIT_ASSERT(chell2);
        CPPUNIT_ASSERT(chell3);
        CPPUNIT_ASSERT_EQUAL(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testDontKillWhenNoneReachedCake() {
        cout << endl << "TEST no matar cuando ninguna llego a cake: ";
        float chell2_x = chell_init_x - 20, chell2_y = chell_init_y;
        float chell3_x = chell_init_x - 30, chell3_y = chell_init_y;
        world->createChell(chell2_x, chell2_y);
        world->createChell(chell3_x, chell3_y);
        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < 3 * STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(!world->allChellsOnCake());
        CPPUNIT_ASSERT(!world->killLastingChell());  // No se elimino
        world->step();  // Permito que se aplique posible 'asesinato'
        chell = world->getChell(0);
        auto chell2 = world->getChell(1);
        auto chell3 = world->getChell(2);
        // Verifico no se elimino
        CPPUNIT_ASSERT(chell);
        CPPUNIT_ASSERT(chell2);
        CPPUNIT_ASSERT(chell3);
        CPPUNIT_ASSERT_EQUAL(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testDontKillWhenAllReachedCake() {
        cout << endl << "TEST no matar cuando todas las chell llegan a cake: ";
        float chell2_x = chell_init_x - 20, chell2_y = chell_init_y;
        float chell3_x = chell_init_x - 30, chell3_y = chell_init_y;
        world->createChell(chell2_x, chell2_y);
        world->createChell(chell3_x, chell3_y);
        auto n_bodies = world->getWorld()->GetBodyCount();
        auto chell2 = world->getChell(1);
        auto chell3 = world->getChell(2);
        chell->move_right();
        chell2->move_right();
        chell3->move_right();
        for (int i = 0; i < 3 * STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT(world->allChellsOnCake());
        CPPUNIT_ASSERT(!world->killLastingChell());  // No se elimino
        world->step();  // Permito que se aplique posible 'asesinato'
        chell = world->getChell(0);
        chell2 = world->getChell(1);
        chell3 = world->getChell(2);
        // Verifico no se elimino
        CPPUNIT_ASSERT(chell);
        CPPUNIT_ASSERT(chell2);
        CPPUNIT_ASSERT(chell3);
        CPPUNIT_ASSERT_EQUAL(n_bodies, world->getWorld()->GetBodyCount());   // Chell ya no existe
        cout << "OK";
    }
};

#endif //PORTAL_TESTCAKE_H
