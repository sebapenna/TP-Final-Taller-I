#ifndef PORTAL_TESTENERGYBALLANDENERGYRECEIVER_H
#define PORTAL_TESTENERGYBALLANDENERGYRECEIVER_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <string>

using std::cout;
using std::endl;

class TestEnergyBallAndEnergyReceiver : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestEnergyBallAndEnergyReceiver);
    CPPUNIT_TEST(testActivateWhenContactFromLeft);
    CPPUNIT_TEST(testActivateWhenContactFromRight);
    CPPUNIT_TEST(testActivateWhenContactFromSouth);
    CPPUNIT_TEST(testActivateWhenContactFromNorth);
    CPPUNIT_TEST(testTransmitterAddedToUpdateVectorAfterReceivingBall);
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    size_t width = 100, height = 200;
    float e_transm_x = 0, e_transm_y = 2;
    // Calculo distancia entre centro de transmisor y receptor (suponiendolos pegados)
    float dist_between_energy_blocks = 2 * ENRG_BLOCK_HALF_LEN;

public:
    void setUp() {
        world = new World(width, height);
//        world->createRockBlock(100, 4, 0, -2); // Piso
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

    void testActivateWhenContactFromLeft() {
        cout << endl << endl << "TEST ENERGY BALL AND ENERGY RECEIVER";
        cout << endl << "TEST activar tras contacto desde izquierda: ";

        float e_rec_x = e_transm_x + dist_between_energy_blocks + 5;    // X centro receptor
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_E);
        world->createEnergyReceiver(e_rec_x, e_transm_y);

        releaseEnergyBall();

        auto e_recv = world->getEnergyReceiver(0);
        CPPUNIT_ASSERT(!e_recv->isActivated());

        int n_bod = world->getWorld()->GetBodyCount();
        float time_elapsed = 0; // Contabilizo tiempo antes que muera bola
        bool e_ball_erased = false;

        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            world->step();
            time_elapsed += TIME_STEP;
            float new_n_bod = world->getWorld()->GetBodyCount();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME && new_n_bod < n_bod)
                e_ball_erased = true;
        }

        CPPUNIT_ASSERT(e_ball_erased);
        CPPUNIT_ASSERT(e_recv->isActivated());
        cout << "OK";
    }

    void testActivateWhenContactFromRight() {
        cout << endl << "TEST activar tras contacto desde derecha: ";

        float e_rec_x = e_transm_x - dist_between_energy_blocks - 5; // X centro receptor
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_O);
        world->createEnergyReceiver(e_rec_x, e_transm_y);

        releaseEnergyBall();

        auto e_recv = world->getEnergyReceiver(0);
        CPPUNIT_ASSERT(!e_recv->isActivated());

        int n_bod = world->getWorld()->GetBodyCount();
        float time_elapsed = 0; // Contabilizo tiempo antes que muera bola
        bool e_ball_erased = false;

        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            world->step();
            time_elapsed += TIME_STEP;
            float new_n_bod = world->getWorld()->GetBodyCount();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME && new_n_bod < n_bod)
                e_ball_erased = true;
        }

        CPPUNIT_ASSERT(e_ball_erased);
        CPPUNIT_ASSERT(e_recv->isActivated());
        cout << "OK";
    }

    void testActivateWhenContactFromSouth() {
        cout << endl << "TEST activar tras contacto desde abajo: ";

        float e_rec_y = e_transm_y + dist_between_energy_blocks + 5;
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_N);
        world->createEnergyReceiver(e_transm_x, e_rec_y);

        releaseEnergyBall();

        auto e_recv = world->getEnergyReceiver(0);
        CPPUNIT_ASSERT(!e_recv->isActivated());
        int n_bod = world->getWorld()->GetBodyCount();
        float time_elapsed = 0; // Contabilizo tiempo antes que muera bola
        bool e_ball_erased = false;

        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            world->step();
            time_elapsed += TIME_STEP;
            float new_n_bod = world->getWorld()->GetBodyCount();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME && new_n_bod < n_bod)
                e_ball_erased = true;
        }

        CPPUNIT_ASSERT(e_ball_erased);
        CPPUNIT_ASSERT(e_recv->isActivated());
        cout << "OK";
    }

    void testActivateWhenContactFromNorth() {
        cout << endl << "TEST activar tras contacto desde arriba: ";

        float e_rec_y = e_transm_y - dist_between_energy_blocks - 5; // y centro receptor
        world->createEnergyTransmitter(e_transm_x, e_transm_y, O_S);
        world->createEnergyReceiver(e_transm_x, e_rec_y);

        releaseEnergyBall();

        auto e_recv = world->getEnergyReceiver(0);
        CPPUNIT_ASSERT(!e_recv->isActivated());
        int n_bod = world->getWorld()->GetBodyCount();
        float time_elapsed = 0; // Contabilizo tiempo antes que muera bola
        bool e_ball_erased = false;

        for (int i = 0; i < STEP_ITERATIONS; ++i) {
            world->step();
            time_elapsed += TIME_STEP;
            float new_n_bod = world->getWorld()->GetBodyCount();
            if (time_elapsed < ENERGY_BALL_MAX_LIFETIME && new_n_bod < n_bod)
                e_ball_erased = true;
        }

        CPPUNIT_ASSERT(e_ball_erased);
        CPPUNIT_ASSERT(e_recv->isActivated());
        cout << "OK";
    }

    void testTransmitterAddedToUpdateVectorAfterReceivingBall() {
        cout << endl << "TEST verificar que se agrega a vector de objetos actualizados luego de "
                        "recibir bola energia: ";
        world->createEnergyReceiver(0, 10);
        auto e_recv = world->getEnergyReceiver(0);
        e_recv->activate();
        world->step();
        auto updated_transm = (EnergyReceiver*) world->getObjectsToUpdate().at(0);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getObjectsToUpdate().size());
        // Verifico es transmisor correcto
        CPPUNIT_ASSERT_EQUAL((size_t) 0, updated_transm->id());
        CPPUNIT_ASSERT_EQUAL(ENERGY_RECEIVER, updated_transm->classId());
        cout << "OK";
    }
};

#endif //PORTAL_TESTENERGYBALLANDENERGYRECEIVER_H
