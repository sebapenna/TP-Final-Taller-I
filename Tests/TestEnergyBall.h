#ifndef PORTAL_TESTENERGYBALL_H
#define PORTAL_TESTENERGYBALL_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/World.h"
#include "Server/constants.h"

using std::cout;
using std::endl;

class TestEnergyBall : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestEnergyBall);
        CPPUNIT_TEST(testContactWithRockBlock);
        CPPUNIT_TEST(testContactWithAcid);
        CPPUNIT_TEST(testContactWithButton);
        CPPUNIT_TEST(testContactWithRock);
        CPPUNIT_TEST(testContactWithEnergyTransmitter);
        CPPUNIT_TEST(testContactWithChell);
        CPPUNIT_TEST(testContactWithEnergyBall);
        CPPUNIT_TEST(testContactWithEnergyBarrier);
        CPPUNIT_TEST(testContactWithOpenGate);
        CPPUNIT_TEST(testContactWithClosedGate);
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

    void releaseEnergyBall() {
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < STEP_ITERATIONS; ++i)
                world->step();
        for (int i = 0; i < STEP_ITERATIONS; ++i)
            world->step(); // Step donde se crea EnergyBall
    }

    void testContactWithRockBlock() {
        cout << endl << endl << "TEST ENERGY BALL";
        cout << endl << "TEST eliminar al contacto con bloque roca: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBalls().at(0);

        float wall_width = 4, wall_height = 10;
        float wall_x = energy_ball->getPositionX() + ENRG_BALL_RADIUS + wall_width;
        float wall_y = wall_height / 2;
        // Creo pared donde colisionar la bola
        world->createRockBlock(wall_width, wall_height, wall_x, wall_y);

        float time_elapsed = 0; // Contabilizo tiempo vida bola energia
        bool ball_deleted = false;
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
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBalls().at(0);

        float acid_x = energy_ball->getPositionX();
        float acid_y = energy_ball->getPositionY() - ENRG_BALL_RADIUS - ACID_HALF_HEIGHT - 1;

        // Creo acido donde colisionar la bola
        world->createAcid(acid_x, acid_y);
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

        CPPUNIT_ASSERT(ball_deleted);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getEnergyBalls().size());
        cout << "OK";
    }

    void testContactWithButton() {
        cout << endl << "TEST eliminar al contacto con boton: ";
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBalls().at(0);

        float button_x = energy_ball->getPositionX();
        float button_y = energy_ball->getPositionY() - ENRG_BALL_RADIUS - BUTTON_HALF_HEIGHT - 1;

        // Creo boton donde colisionar la bola
        world->createButton(0, button_x, button_y);
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

        CPPUNIT_ASSERT(ball_deleted);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getEnergyBalls().size());
        cout << "OK";
    }

    void testContactWithRock() {
        cout << endl << "TEST eliminar al contacto con roca: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBalls().at(0);

        float rock_x = energy_ball->getPositionX();
        float rock_y = energy_ball->getPositionY() - ENRG_BALL_RADIUS - ROCK_HALF_LEN - 1;

        // Creo boton donde colisionar la bola
        world->createRock(rock_x, rock_y);
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

        CPPUNIT_ASSERT(ball_deleted);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getEnergyBalls().size());
        cout << "OK";
    }

    void testContactWithEnergyTransmitter() {
        cout << endl << "TEST eliminar al contacto con transmisor de energia: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        releaseEnergyBall();
        auto e_ball = world->getEnergyBalls().at(0);

        float e_transm_2_x = e_ball->getPositionX();
        float e_transm_2_y = e_ball->getPositionY() - ENRG_BALL_RADIUS - ENRG_BLOCK_HALF_LEN- 1;

        // Creo tranmisor donde colisionar la bola
        world->createEnergyTransmitter(e_transm_2_x, e_transm_2_y, O_E);
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

        CPPUNIT_ASSERT(ball_deleted);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getEnergyBalls().size());
        cout << "OK";
    }

    void testContactWithChell() {
        cout << endl << "TEST eliminar al contacto con chell: ";

        world->createRockBlock(100, 4, 0, -2); // Piso
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        releaseEnergyBall();
        auto energy_ball = world->getEnergyBalls().at(0);

        float chell_x = energy_ball->getPositionX() + ENRG_BALL_RADIUS + CHELL_HALF_WIDTH + 1;
        float chell_y = energy_ball->getPositionY();

        // Creo chell donde colisionar la bola
        world->createChell(chell_x, chell_y, 0);
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

        CPPUNIT_ASSERT(ball_deleted);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getEnergyBalls().size());
        cout << "OK";
    }

    void testContactWithEnergyBall() {
        cout << endl << "TEST ignorar contacto con otra bola de energia: ";

        float e_transm_2_x = e_transm_x + 4 * ENRG_BALL_RADIUS + 2 * ENRG_BLOCK_HALF_LEN + 2;
        float e_transm_2_y = e_transm_y;
        // Creo transmisores en sentido opuesto para que choquen bolas energia
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        world->createEnergyTransmitter(e_transm_2_x, e_transm_2_y, O_O);
        releaseEnergyBall();
        auto e_ball_1 = world->getEnergyBalls().at(0); // Bola de transm1
        auto e_ball_2 = world->getEnergyBalls().at(1); // Bola de transm2

        // Verifico bola 1 esta a la izquierda de la bola 2
        CPPUNIT_ASSERT(e_ball_1->getPositionX() < e_ball_2->getPositionX());

        int n_bodies = world->getWorld()->GetBodyCount();
        bool balls_ignored = false;
        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            world->step();
            // Verifico que una bola paso a la otra
            // IMPORTANTE: primero compruebo n_bodies para asegurarme que no fueron eliminados
            if ((n_bodies == world->getWorld()->GetBodyCount()) &&
            (e_ball_1->getPositionX() > e_ball_2->getPositionX()))
                    balls_ignored = true;
        }

        CPPUNIT_ASSERT(balls_ignored);
        cout << "OK";
    }

    void testContactWithEnergyBarrier() {
        cout << endl << "TEST ignorar contacto con barrera energia: ";
        float barrier_x = e_transm_x + 4 * ENRG_BALL_RADIUS + BARRIER_HALF_WIDTH + 2;
        float barrier_y = BARRIER_HALF_LENGTH;
        // Creo transmisores en sentido opuesto para que choquen bolas energia
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        world->createEnergyBarrier(barrier_x, barrier_y, O_V);
        releaseEnergyBall();
        auto e_ball = world->getEnergyBalls().at(0); // Bola de transm1

        int n_bodies = world->getWorld()->GetBodyCount();
        bool barrier_ignored = false;
        for (int i = 0; i < 2 * STEP_ITERATIONS; ++i) {
            world->step();
            // Verifico que bola paso la barrera
            // IMPORTANTE: primero compruebo n_bodies para asegurarme que no fueron eliminados
            if ((n_bodies == world->getWorld()->GetBodyCount()) &&
            (e_ball->getPositionX() > barrier_x))
                barrier_ignored = true;
        }

        CPPUNIT_ASSERT(barrier_ignored);
        cout << "OK";
    }

    void testContactWithOpenGate() {
        cout << endl << "TEST ignorar contacto con compuerta abierta: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        releaseEnergyBall();
        auto e_ball = world->getEnergyBalls().at(0); // Bola de transm1

        world->createButton(0, 100, 100); // Boton para abrir gate
        auto button  = world->getButtons().at(0);
        button->activate(); // Activo boton

        float gate_x = e_ball->getPositionX() + ENRG_BALL_RADIUS + GATE_HALF_WIDTH + 2;
        float gate_y = GATE_HALF_HEIGHT;
        world->createGate(0, gate_x, gate_y, {0}, {});
        auto gate = world->getGates().at(0);

        int n_bodies = world->getWorld()->GetBodyCount();
        bool gate_ignored = false;
        for (int i = 0; i < 2 * STEP_ITERATIONS; ++i) {
            world->step();
            // Verifico que bola paso la compuerta
            // IMPORTANTE: primero compruebo n_bodies para asegurarme que no fueron eliminados
            if ((n_bodies == world->getWorld()->GetBodyCount()) &&
            (e_ball->getPositionX() > gate_x))
                gate_ignored = true;
        }

        CPPUNIT_ASSERT(gate->isOpen());
        CPPUNIT_ASSERT(gate_ignored);
        cout << "OK";
    }


    void testContactWithClosedGate() {
        cout << endl << "TEST chocar con compuerta cerrada: ";

        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        releaseEnergyBall();
        auto e_ball = world->getEnergyBalls().at(0); // Bola de transm1
        world->createButton(0, 100, 100); // Boton para abrir gate

        float gate_x = e_ball->getPositionX() + ENRG_BALL_RADIUS + GATE_HALF_WIDTH + 2;
        float gate_y = GATE_HALF_HEIGHT;
        world->createGate(0, gate_x, gate_y, {0}, {});
        auto gate = world->getGates().at(0);

        for (int i = 0; i < 2 * STEP_ITERATIONS; ++i)
            world->step();

        CPPUNIT_ASSERT(!gate->isOpen());
        CPPUNIT_ASSERT_LESS(gate_x, e_ball->getPositionX());
        cout << "OK";
    }
};

#endif //PORTAL_TESTENERGYBALL_H
