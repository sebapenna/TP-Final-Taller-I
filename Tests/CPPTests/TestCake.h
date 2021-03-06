#ifndef PORTAL_TESTCAKE_H
#define PORTAL_TESTCAKE_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <Common/exceptions.h>
#include <string>

using std::cout;
using std::endl;
using std::make_shared;

class TestCake : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestCake);
        CPPUNIT_TEST(testChellReachCake);
        CPPUNIT_TEST(testOnlyOneChellReachCake);
        CPPUNIT_TEST(testAllChellsReachCake);
        CPPUNIT_TEST(testKillOnlyChellThatDidntReachCake);
        CPPUNIT_TEST(testDontKillWhenNotAllReachedCake);
        CPPUNIT_TEST(testDontKillWhenNoneReachedCake);
        CPPUNIT_TEST(testDontKillWhenAllReachedCake);
        CPPUNIT_TEST(testRemoveFromWantToKillWhenLeavingCake);
        CPPUNIT_TEST(testLeavesCakeReturnsAndKills);
    CPPUNIT_TEST_SUITE_END();

private:
    std::shared_ptr<Configuration> ptr;
    Configuration *config;
    World *world;
    Chell *chell;
    size_t width = 100;
    size_t height = 200;
    float chell_init_x = 0, chell_init_y = 2;
    float cake_x = 10, cake_y = 2;

public:
    void setUp() {
        ptr = make_shared<Configuration>();
config = ptr.get();
        world = new World(width, height, ptr);
        auto data = make_shared<RockBlockData>(100, 4, 0, -2); // Piso
        world->createCollidable(data);
        auto data2 = make_shared<ChellData>(0, chell_init_x, chell_init_y);
        world->createCollidable(data2);
        auto data3 = make_shared<CakeData>(cake_x, cake_y);
        world->createCollidable(data3);
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
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            if (chell->reachedCake())
                reached_cake = true;
        }
        CPPUNIT_ASSERT(reached_cake);
        cout << "OK";
    }

    void testOnlyOneChellReachCake() {
        cout << endl << "TEST solo una chell llega a cake: ";
        float chell2_x = chell_init_x - 20, chell2_y = chell_init_y;
        auto data = make_shared<ChellData>(0, chell2_x, chell2_y);
        world->createCollidable(data);
        chell->move_right();
        for (int i = 0; i < config->getFps(); i++)
            world->step();
        auto chell2 = world->getChell(1);
        CPPUNIT_ASSERT(chell->reachedCake());
        CPPUNIT_ASSERT(!chell2->reachedCake());
        cout << "OK";
    }

    void testAllChellsReachCake() {
        cout << endl << "TEST todas las chell llegan a cake: ";
        float chell2_x = chell_init_x - 20, chell2_y = chell_init_y;
        float chell3_x = chell_init_x - 30, chell3_y = chell_init_y;
        auto data = make_shared<ChellData>(1, chell2_x, chell2_y);
        world->createCollidable(data);
        auto data2 = make_shared<ChellData>(2, chell3_x, chell3_y);
        world->createCollidable(data2);
        auto chell2 = world->getChell(1);
        auto chell3 = world->getChell(2);
        chell->move_right();
        chell2->move_right();
        chell3->move_right();
        for (int i = 0; i < 3 * config->getFps(); i++)
            world->step();
        CPPUNIT_ASSERT(chell2->reachedCake());
        CPPUNIT_ASSERT(chell3->reachedCake());
        cout << "OK";
    }

    void testKillOnlyChellThatDidntReachCake() {
        cout << endl << "TEST matar a unica chell que no llega a cake: ";
        float chell2_x = chell_init_x - 20, chell2_y = chell_init_y;
        float chell3_x = chell_init_x - 30, chell3_y = chell_init_y;
        auto data = make_shared<ChellData>(1, chell2_x, chell2_y);
        world->createCollidable(data);
        auto data2 = make_shared<ChellData>(1, chell3_x, chell3_y);
        world->createCollidable(data2);
        auto chell2 = world->getChell(1);
        auto chell3 = world->getChell(2);
        chell->move_right();
        chell2->move_right();
        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < 3 * config->getFps(); i++)
            world->step();
        CPPUNIT_ASSERT(chell->reachedCake());
        CPPUNIT_ASSERT(chell2->reachedCake());
        CPPUNIT_ASSERT(!chell3->reachedCake());
        world->killLastingChell(0); // Indico que chells de id 0 y 1 quieren matar a la restante
        world->killLastingChell(1);
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
        auto data = make_shared<ChellData>(1, chell2_x, chell2_y);
        world->createCollidable(data);
        auto data2 = make_shared<ChellData>(2, chell3_x, chell3_y);
        world->createCollidable(data2);
        chell->move_right();
        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < 3 * config->getFps(); i++)
            world->step();
        auto chell2 = world->getChell(1);
        auto chell3 = world->getChell(2);
        CPPUNIT_ASSERT(chell->reachedCake());
        CPPUNIT_ASSERT(!chell2->reachedCake());
        CPPUNIT_ASSERT(!chell3->reachedCake());
        world->killLastingChell(0); // Indico que chells de id 0 y 1 quieren matar a la restante
        world->killLastingChell(1);
        world->step();  // Permito que se aplique posible 'asesinato'
        chell = world->getChell(0);
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
        auto data = make_shared<ChellData>(1, chell2_x, chell2_y);
        world->createCollidable(data);
        auto data2 = make_shared<ChellData>(2, chell3_x, chell3_y);
        world->createCollidable(data2);
        auto n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < 3 * config->getFps(); i++)
            world->step();
        auto chell2 = world->getChell(1);
        auto chell3 = world->getChell(2);
        CPPUNIT_ASSERT(!chell->reachedCake());
        CPPUNIT_ASSERT(!chell2->reachedCake());
        CPPUNIT_ASSERT(!chell3->reachedCake());
        world->killLastingChell(0); // Indico que chells de id 0, 1 y 2 quieren matar a la restante
        world->killLastingChell(1);
        world->killLastingChell(2);
        world->step();  // Permito que se aplique posible 'asesinato'
        chell = world->getChell(0);
        chell2 = world->getChell(1);
        chell3 = world->getChell(2);
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
        auto data = make_shared<ChellData>(1, chell2_x, chell2_y);
        world->createCollidable(data);
        auto data2 = make_shared<ChellData>(2, chell3_x, chell3_y);
        world->createCollidable(data2);
        auto n_bodies = world->getWorld()->GetBodyCount();
        auto chell2 = world->getChell(1);
        auto chell3 = world->getChell(2);
        chell->move_right();
        chell2->move_right();
        chell3->move_right();
        for (int i = 0; i < 3 * config->getFps(); i++)
            world->step();
        CPPUNIT_ASSERT(chell->reachedCake());
        CPPUNIT_ASSERT(chell2->reachedCake());
        CPPUNIT_ASSERT(chell3->reachedCake());
        world->killLastingChell(0); // Indico que chells de id 0,1 y 2 quieren matar a la restante
        world->killLastingChell(1);
        world->killLastingChell(2);
        world->step();  // Permito que se aplique posible 'asesinato'
        chell = world->getChell(0);
        chell2 = world->getChell(1);
        chell3 = world->getChell(2);
        // Verifico no se elimino
        CPPUNIT_ASSERT(chell);
        CPPUNIT_ASSERT(chell2);
        CPPUNIT_ASSERT(chell3);
        CPPUNIT_ASSERT_EQUAL(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testRemoveFromWantToKillWhenLeavingCake() {
        cout << endl << "TEST chell es eliminada de las que quieren matar cuando se aleja de "
                        "cake: ";
        float chell2_x = chell_init_x - 20, chell2_y = chell_init_y;
        float chell3_x = chell_init_x - 30, chell3_y = chell_init_y;
        auto data = make_shared<ChellData>(1, chell2_x, chell2_y);
        world->createCollidable(data);
        auto data2 = make_shared<ChellData>(2, chell3_x, chell3_y);
        world->createCollidable(data2);
        auto n_bodies = world->getWorld()->GetBodyCount();
        auto chell2 = world->getChell(1);
        auto chell3 = world->getChell(2);
        chell->move_right();
        chell2->move_right();
        for (int i = 0; i < 3 * config->getFps(); i++)
            world->step();
        CPPUNIT_ASSERT(chell->reachedCake());
        CPPUNIT_ASSERT(chell2->reachedCake());
        CPPUNIT_ASSERT(!chell3->reachedCake());
        world->killLastingChell(0); // Indico que chell de id 0  quieren matar a la restante
        chell->move_left(); // Alejo chell de cake
        for (int i = 0; i < 3 * config->getFps(); i++)
            world->step();
        CPPUNIT_ASSERT(!chell->reachedCake());
        world->killLastingChell(1); // Chell 2 quiere matar
        world->step();  // Si ambos chells siguieran en cake se eliminaria chell3
        CPPUNIT_ASSERT(chell);
        CPPUNIT_ASSERT(chell2);
        CPPUNIT_ASSERT(chell3);
        CPPUNIT_ASSERT_EQUAL(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testLeavesCakeReturnsAndKills() {
        cout << endl << "TEST chell se aleja de cake, vuelve y decide matar: ";
        float chell2_x = chell_init_x - 20, chell2_y = chell_init_y;
        float chell3_x = chell_init_x - 30, chell3_y = chell_init_y;
        auto data = make_shared<ChellData>(1, chell2_x, chell2_y);
        world->createCollidable(data);
        auto data2 = make_shared<ChellData>(2, chell3_x, chell3_y);
        world->createCollidable(data2);
        auto n_bodies = world->getWorld()->GetBodyCount();
        auto chell2 = world->getChell(1);
        auto chell3 = world->getChell(2);
        chell->move_right();
        chell2->move_right();
        for (int i = 0; i < 3 * config->getFps(); i++)
            world->step();
        world->killLastingChell(0); // Indico que chell de id 0  quiere matar a la restante
        chell->move_left(); // Alejo chell de cake
        for (int i = 0; i < 3 * config->getFps(); i++)
            world->step();
        world->killLastingChell(1); // Chell 2 quiere matar
        chell->move_right();
        for (int i = 0; i < 5 * config->getFps(); i++)
            world->step();
        CPPUNIT_ASSERT(chell->reachedCake());
        world->killLastingChell(0); // Indico que chell de id 0 quiere matar a la restante
        world->step();  // Permito que se aplique posible 'asesinato'
        chell3 = world->getChell(2);
        CPPUNIT_ASSERT(chell);
        CPPUNIT_ASSERT(chell2);
        CPPUNIT_ASSERT(!chell3);    // Chell3 eliminada
        CPPUNIT_ASSERT_LESS(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }
};

#endif //PORTAL_TESTCAKE_H
