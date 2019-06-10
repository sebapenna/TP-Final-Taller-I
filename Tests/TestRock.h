#ifndef PORTAL_TESTROCK_H
#define PORTAL_TESTROCK_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <Common/exceptions.h>
#include <string>

using std::cout;
using std::endl;

class TestRock : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestRock);
        CPPUNIT_TEST( testCreate );
        CPPUNIT_TEST( testFallsWithGravity );
        CPPUNIT_TEST( testRemainsStillOnGround );
        CPPUNIT_TEST( testContactWithBarrier );
        CPPUNIT_TEST( testContactWithEnergyBall );
        CPPUNIT_TEST( testAddedToUpdateVectorAfterMoving );
        CPPUNIT_TEST( testAddedToDeleteVectorAfterDead );
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    Rock *rock1;
    Rock *rock2;
    size_t width = 100;
    size_t height = 200;
    float rock1_x = 0, rock1_y = 2, rock2_x = 6, rock2_y = 4;
    int init_n_bodies;

public:
    void setUp() {
        world = new World(width, height);
        world->createRockBlock(100, 4, 0, -2); // Piso
        world->createRock(rock1_x, rock1_y);
        world->createRock(rock2_x, rock2_y);
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
        CPPUNIT_ASSERT_EQUAL(rock1_x, rock1->getPositionX());
        CPPUNIT_ASSERT_EQUAL(rock1_y, rock1->getPositionY());
        CPPUNIT_ASSERT_EQUAL((size_t) 0, rock1->getId());
        CPPUNIT_ASSERT_EQUAL(rock2_x, rock2->getPositionX());
        CPPUNIT_ASSERT_EQUAL(rock2_y, rock2->getPositionY());
        CPPUNIT_ASSERT_EQUAL((size_t) 1, rock2->getId());
        cout << "OK";
    }

    void testFallsWithGravity() {
        cout << endl << "TEST cae con gravedad: ";
        for (int i = 0; i < 200; i++)
            world->step();
        float y_diff = rock2->getPositionY() - ROCK_HALF_LEN;
        float x_diff = rock2->getPositionX() - rock2_x;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, x_diff);
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, y_diff);
        cout << "OK";
    }

    void testRemainsStillOnGround() {
        cout << endl << "TEST queda quieta sobre una superficie: ";
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        float y_diff = rock1->getPositionY() - rock1_y;
        float x_diff = rock1->getPositionX() - rock1_x;
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, x_diff);
        CPPUNIT_ASSERT_LESSEQUAL(DELTA_POS, y_diff);
        cout << "OK";
    }

    void testContactWithBarrier() {
        cout << endl << "TEST eliminar ante contacto con barrera energia: ";
        float barrier_x = 10, barrier_y = BARRIER_HALF_LENGTH;
        world->createEnergyBarrier(barrier_x, barrier_y, O_V);
        auto n_bodies = world->getWorld()->GetBodyCount();
        rock1->teletransport(barrier_x, barrier_y);
        for (int i = 0; i < STEP_ITERATIONS; i++)
            world->step();
        CPPUNIT_ASSERT_EQUAL(n_bodies - 1, world->getWorld()->GetBodyCount());
        CPPUNIT_ASSERT_EQUAL((Rock*)nullptr, world->getRock(0));
        cout << "OK";
    }

    void testContactWithEnergyBall() {
        cout << endl << "TEST quedar en lugar ante contacto con energy ball: ";

        float e_transm_x = rock1_x - ENRG_BALL_RADIUS - ROCK_HALF_LEN - 1;
        float e_transm_y = rock1_y ;

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i)
                world->step();
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall

        float pre_contact_pos_y = rock1->getPositionY();
        float pre_contact_pos_x = rock1->getPositionX();

        int n_bodies = world->getWorld()->GetBodyCount();
        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            time_elapsed += TIME_STEP;
            world->step();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }
        CPPUNIT_ASSERT_EQUAL(pre_contact_pos_x, rock1->getPositionX());
        float diff_y = pre_contact_pos_y - rock1->getPositionY();
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        CPPUNIT_ASSERT(ball_deleted);
        cout << "OK";
    }

    void testAddedToUpdateVectorAfterMoving() {
        cout << endl << "TEST verificar que se agrega a vector de objetos actualizados luego de "
                        "movimiento: ";
        CPPUNIT_ASSERT(world->getObjectsToUpdate().empty());
        for (int i = 0; i < 5; i++)
            world->step();  // Realizo varias iteraciones para que cuerpo acelere con gravedad
        // Roca 2 esta cayendo por gravedad, verifico se agrego elemento a vector y que no se
        // agrego la roca 1 (quieta)
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getObjectsToUpdate().size());
        // Verifico no se lo agrego a vector de elementos a eliminar
        CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
        // Verifico roca correcta
        auto update_rock = (Rock*) world->getObjectsToUpdate().at(0);
        CPPUNIT_ASSERT_EQUAL(rock2_x, update_rock->getPositionX());
        CPPUNIT_ASSERT_EQUAL((size_t) 1, update_rock->getId());
        cout << "OK";
    }

    void testAddedToDeleteVectorAfterDead() {
        cout << endl << "TEST verificar que se agrega a vector de objetos a eliminar luego de "
                        "morir: ";
        CPPUNIT_ASSERT(world->getObjectsToDelete().empty());
        float barrier_x = 10, barrier_y = BARRIER_HALF_LENGTH;
        world->createEnergyBarrier(barrier_x, barrier_y, O_V);
        rock2->teletransport(barrier_x, barrier_y); // Coloco sobre la barrera
        world->step();
        // Roca 2 debe ser eliminada
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getObjectsToDelete().size());
        // Verifico no se lo agrego a vector de elementos a actualizar
        CPPUNIT_ASSERT(world->getObjectsToUpdate().empty());
        // Verifico roca correcta (id y classId)
        std::pair<size_t, std::string> delete_rock_data = world->getObjectsToDelete().at(0);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, delete_rock_data.first);
        CPPUNIT_ASSERT_EQUAL((std::string) ROCK, delete_rock_data.second);
        cout << "OK";
    }

    // todo: TESTS CON CHELL MOVIENDOLO
};
#endif //PORTAL_TESTROCK_H
