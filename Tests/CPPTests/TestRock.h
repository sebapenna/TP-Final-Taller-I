#ifndef PORTAL_TESTROCK_H
#define PORTAL_TESTROCK_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <Common/exceptions.h>
#include <string>

using std::cout;
using std::endl;
using std::make_shared;

class TestRock : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestRock);
        CPPUNIT_TEST( testCreate );
        CPPUNIT_TEST( testFallsWithGravity );
        CPPUNIT_TEST( testRemainsStillOnGround );
        CPPUNIT_TEST( testContactWithBarrier );
        CPPUNIT_TEST( testContactWithEnergyBall );
        CPPUNIT_TEST( testAddedToDeleteVectorAfterDead );
    CPPUNIT_TEST_SUITE_END();

private:
    std::shared_ptr<Configuration> ptr;
    Configuration *config;
    World *world;
    Rock *rock1;
    Rock *rock2;
    size_t width = 100;
    size_t height = 200;
    float rock1_x = 0, rock1_y = 2, rock2_x = 6, rock2_y = 4;
    int init_n_bodies;

public:
    void setUp() {
        ptr = make_shared<Configuration>();
config = ptr.get();
        world = new World(width, height, ptr);
        auto data = make_shared<RockBlockData>(100, 4, 0, -2); // Piso
        world->createCollidable(data);
        auto data2 = make_shared<RockData>(rock1_x, rock1_y);
        world->createCollidable(data2);
        auto data3 = make_shared<RockData>(rock2_x, rock2_y);
        world->createCollidable(data3);
        init_n_bodies = 3;  // Cantidad de bodies que creo al inicio
        rock1 = world->getRock(0);
        rock2 = world->getRock(1);
    }

    void tearDown() {
        delete world;
    }

    void testCreate() {
        cout << endl << endl << "TEST ROCK";
        cout << endl << "TEST crear correctamente: ";
        CPPUNIT_ASSERT_EQUAL(init_n_bodies, world->getWorld()->GetBodyCount());
        CPPUNIT_ASSERT_EQUAL(rock1_x, rock1->x());
        CPPUNIT_ASSERT_EQUAL(rock1_y, rock1->y());
        CPPUNIT_ASSERT_EQUAL((size_t) 0, rock1->id());
        CPPUNIT_ASSERT_EQUAL(rock2_x, rock2->x());
        CPPUNIT_ASSERT_EQUAL(rock2_y, rock2->y());
        CPPUNIT_ASSERT_EQUAL((size_t) 1, rock2->id());
        cout << "OK";
    }

    void testFallsWithGravity() {
        cout << endl << "TEST cae con gravedad: ";
        for (int i = 0; i < 200; i++)
            world->step();
        float y_diff = rock2->y() - config->getRockHalfLen();
        float x_diff = rock2->x() - rock2_x;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, x_diff);
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, y_diff);
        cout << "OK";
    }

    void testRemainsStillOnGround() {
        cout << endl << "TEST queda quieta sobre una superficie: ";
        for (int i = 0; i < config->getFps(); i++)
            world->step();
        float y_diff = rock1->y() - rock1_y;
        float x_diff = rock1->x() - rock1_x;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, x_diff);
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, y_diff);
        cout << "OK";
    }

    void testContactWithBarrier() {
        cout << endl << "TEST eliminar ante contacto con barrera energia: ";
        float barrier_x = 10, barrier_y = config->getBarrierHalfLen();
        auto data = make_shared<EnergyBarrierData>(barrier_x, barrier_y, "V");
        world->createCollidable(data);
        auto n_bodies = world->getWorld()->GetBodyCount();
        rock1->teletransport(barrier_x, barrier_y);
        for (int i = 0; i < config->getFps(); i++)
            world->step();
        CPPUNIT_ASSERT_EQUAL(n_bodies - 1, world->getWorld()->GetBodyCount());
        CPPUNIT_ASSERT_EQUAL((Rock*)nullptr, world->getRock(0));
        cout << "OK";
    }

    void testContactWithEnergyBall() {
        cout << endl << "TEST quedar en lugar ante contacto con energy ball: ";

        float e_transm_x = rock1_x - config->getEnergyBallRadius() - config->getRockHalfLen() - 1;
        float e_transm_y = rock1_y ;

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);    // Lanzara bola contra chell
        for (int j = 1; j < config->getTimeToReleaseEnrgBall(); ++j)
            for (int i = 0; i < config->getFps(); ++i)
                world->step();
        for (int i = 0; i < config->getFps(); ++i)
            world->step(); // Step donde se crea EnergyBall

        float pre_contact_pos_y = rock1->y();
        float pre_contact_pos_x = rock1->x();

        int n_bodies = world->getWorld()->GetBodyCount();
        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        for (int i = 0; i < config->getFps(); ++i) {
            time_elapsed += (1 / config->getFps());
            world->step();
            if (time_elapsed < config->getEnergyBallLifetime() &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }
        CPPUNIT_ASSERT_EQUAL(pre_contact_pos_x, rock1->x());
        float diff_y = pre_contact_pos_y - rock1->y();
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        CPPUNIT_ASSERT(ball_deleted);
        cout << "OK";
    }

    void testAddedToDeleteVectorAfterDead() {
        cout << endl << "TEST verificar que se agrega a vector de objetos a eliminar luego de "
                        "morir: ";
        CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
        float barrier_x = 10, barrier_y = config->getBarrierHalfLen();
        auto data = make_shared<EnergyBarrierData>(barrier_x, barrier_y, "V");
        world->createCollidable(data);
        rock2->teletransport(barrier_x, barrier_y); // Coloco sobre la barrera
        world->step();
        // Roca 2 debe ser eliminada
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getObjectsToDelete().size());
        // Verifico no se lo agrego a vector de elementos a actualizar
        CPPUNIT_ASSERT(world->getObjectsToUpdate().empty());
        // Verifico roca correcta (id y classId)
        auto delete_rock_data = world->getObjectsToDelete().at(0);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, delete_rock_data.first);
        CPPUNIT_ASSERT_EQUAL(ROCK, delete_rock_data.second);
        cout << "OK";
    }

    // todo: TESTS CON CHELL MOVIENDOLO
};
#endif //PORTAL_TESTROCK_H
