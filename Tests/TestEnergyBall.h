#ifndef PORTAL_TESTENERGYBALL_H
#define PORTAL_TESTENERGYBALL_H

#include <cppunit/extensions/HelperMacros.h>
#include "src/World.h"
#include "src/constants.h"

using std::cout;
using std::endl;

class TestEnergyBall : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestEnergyBall);
        CPPUNIT_TEST(testContactWithRockBlock);
        CPPUNIT_TEST(testContactWithAcid);
        CPPUNIT_TEST(testContactWithButton);
        CPPUNIT_TEST(testContactWithRock);
        CPPUNIT_TEST(testContactWithChell);
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    size_t width = 100, height = 200;
    float e_transm_x = 0, e_transm_y = 2;

public:
    void setUp() {
        world = new World(width, height);
    }

    void tearDown() {
        delete world;
    }

    void testContactWithRockBlock() {
        cout << endl << endl << "TEST ENERGY BALL";
        cout << endl << "TEST eliminar al contacto con bloque roca: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            world->step(); // Step donde se crea EnergyBall
        }
        auto energy_ball = world->getEnergyBalls().at(0);
        float wall_width = 4, wall_height = 10;
        float wall_x = energy_ball->getPositionX() + ENRG_BALL_RADIUS +
                wall_width;
        float wall_y = wall_height / 2;
        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        // Creo pared donde colisionar la bola
        world->createRockBlock(wall_width, wall_height, wall_x, wall_y);
        int n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            time_elapsed += TIME_STEP;
            world->step();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }
        CPPUNIT_ASSERT(ball_deleted);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getEnergyBalls().size());
        cout << "OK";
    }

    void testContactWithAcid() {
        cout << endl << "TEST eliminar al contacto con acido: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            world->step(); // Step donde se crea EnergyBall
        }
        auto energy_ball = world->getEnergyBalls().at(0);
        float acid_x = energy_ball->getPositionX();
        float acid_y = energy_ball->getPositionY() - ENRG_BALL_RADIUS -
                ACID_HALF_HEIGHT - 1;
        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        // Creo acido donde colisionar la bola
        world->createAcid(acid_x, acid_y);
        int n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            time_elapsed += TIME_STEP;
            world->step();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }
        CPPUNIT_ASSERT(ball_deleted);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getEnergyBalls().size());
        cout << "OK";
    }

    void testContactWithButton() {
        cout << endl << "TEST eliminar al contacto con boton: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            world->step(); // Step donde se crea EnergyBall
        }
        auto energy_ball = world->getEnergyBalls().at(0);
        float button_x = energy_ball->getPositionX();
        float button_y = energy_ball->getPositionY() - ENRG_BALL_RADIUS -
                BUTTON_HALF_HEIGHT - 1;
        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        // Creo boton donde colisionar la bola
        world->createButton(0, button_x, button_y);
        int n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            time_elapsed += TIME_STEP;
            world->step();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }
        CPPUNIT_ASSERT(ball_deleted);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getEnergyBalls().size());
        cout << "OK";
    }

    void testContactWithRock() {
        cout << endl << "TEST eliminar al contacto con roca: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            world->step(); // Step donde se crea EnergyBall
        }
        auto energy_ball = world->getEnergyBalls().at(0);
        float rock_x = energy_ball->getPositionX();
        float rock_y = energy_ball->getPositionY() - ENRG_BALL_RADIUS -
                ROCK_HALF_HEIGHT - 1;
        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        // Creo boton donde colisionar la bola
        world->createRock(rock_x, rock_y);
        int n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            time_elapsed += TIME_STEP;
            world->step();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }
        CPPUNIT_ASSERT(ball_deleted);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getEnergyBalls().size());
        cout << "OK";
    }

    void testContactWithChell() {
        cout << endl << "TEST eliminar al contacto con chell: ";
        world->createRockBlock(100, 4, 0, -2); // Piso
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i) {
                world->step();
                auto vec = world->getEnergyBalls();
                CPPUNIT_ASSERT_EQUAL((size_t) 0, vec.size());
            }
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            world->step(); // Step donde se crea EnergyBall
        }
        auto energy_ball = world->getEnergyBalls().at(0);
        float chell_x = energy_ball->getPositionX() + ENRG_BALL_RADIUS +
                CHELL_HALF_WIDTH + 1;
        float chell_y = energy_ball->getPositionY();
        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
        // Creo chell donde colisionar la bola
        world->createChell(chell_x, chell_y, 0);
        int n_bodies = world->getWorld()->GetBodyCount();
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            time_elapsed += TIME_STEP;
            world->step();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME &&
                world->getWorld()->GetBodyCount() < n_bodies)
                ball_deleted = true;    // Bola colisiono con pared
        }
        CPPUNIT_ASSERT(ball_deleted);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getEnergyBalls().size());
        cout << "OK";
    }
};

#endif //PORTAL_TESTENERGYBALL_H
