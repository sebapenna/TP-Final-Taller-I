#ifndef PORTAL_TESTENERGYBALLANDENERGYTRANSMITTER_H
#define PORTAL_TESTENERGYBALLANDENERGYTRANSMITTER_H

#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"

using std::cout;
using std::endl;
using std::make_shared;

class TestEnergyBallAndEnergyTransmitter : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestEnergyBallAndEnergyTransmitter);
        CPPUNIT_TEST(testCreateNorth);
        CPPUNIT_TEST(testCreateSouth);
        CPPUNIT_TEST(testCreateEast);
        CPPUNIT_TEST(testCreateWest);
        CPPUNIT_TEST(testCreateMoreThanOne);
        CPPUNIT_TEST(testMovesNorth);
        CPPUNIT_TEST(testMovesSouth);
        CPPUNIT_TEST(testMovesEast);
        CPPUNIT_TEST(testMovesWest);
        CPPUNIT_TEST(testMovesNorthWithFixedSpeed);
        CPPUNIT_TEST(testMovesSouthWithFixedSpeed);
        CPPUNIT_TEST(testMovesEastWithFixedSpeed);
        CPPUNIT_TEST(testMovesWestWithFixedSpeed);
        CPPUNIT_TEST(testDiesAfterLifetimeReached);
        CPPUNIT_TEST(testTransmitterAddedToUpdateVectorAfterReleasingBall);
    CPPUNIT_TEST_SUITE_END();

private:
    std::shared_ptr<Configuration> ptr;
    Configuration *config;
    World *world;
    size_t width = 100, height = 200;
    float e_transm_x = 0, e_transm_y = ENRG_BLOCK_HALF_LEN;
    // Calculo distancia entre centro de transmisor y bola energia (suponiendolos pegados)
    const float dist_transm_to_enrgball = ENRG_BLOCK_HALF_LEN + ENRG_BALL_RADIUS;

public:
    void setUp() {
        ptr = make_shared<Configuration>();
config = ptr.get();
        world = new World(width, height, ptr);
//        world->createRockBlock(100, 4, 0, -2); // Piso
    }

    void tearDown() {
        delete world;
    }

    void releaseEnergyBall() {
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < config->getFps(); ++i)
                world->step();
        for (int i = 0; i < config->getFps(); ++i)
            world->step(); // Step donde se crea EnergyBall
    }

    void testCreateNorth() {
        cout << endl << endl << "TEST ENERGY BALL AND ENERGY TRANSMITTER";
        cout << endl << "TEST crear correctamente en direccion Norte: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "N");
        world->createCollidable(data);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < config->getFps(); ++i) {
                world->step();
                CPPUNIT_ASSERT_EQUAL((EnergyBall*) nullptr, world->getEnergyBall(0));
            }
        for (int i = 0; i < config->getFps(); ++i)
            world->step(); // Step donde se crea EnergyBall

        float new_y = e_transm_y + dist_transm_to_enrgball;
        auto energy_ball = world->getEnergyBall(0);

        CPPUNIT_ASSERT_EQUAL((EnergyBall*) nullptr, world->getEnergyBall(1)); // No existe otra bola
        CPPUNIT_ASSERT_EQUAL(e_transm_x, energy_ball->x());
        CPPUNIT_ASSERT_GREATEREQUAL(new_y, energy_ball->y());
        cout << "OK";
    }

    void testCreateSouth() {
        cout << endl << "TEST crear correctamente en direccion Sur: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "S");
        world->createCollidable(data);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < config->getFps(); ++i) {
                world->step();
                CPPUNIT_ASSERT_EQUAL((EnergyBall*) nullptr, world->getEnergyBall(0));
            }
        for (int i = 0; i < config->getFps(); ++i)
            world->step(); // Step donde se crea EnergyBall

        float new_y = e_transm_y - dist_transm_to_enrgball;
        auto energy_ball = world->getEnergyBall(0);

        CPPUNIT_ASSERT_EQUAL((EnergyBall*) nullptr, world->getEnergyBall(1)); // No existe otra bola
        CPPUNIT_ASSERT_EQUAL(e_transm_x, energy_ball->x());
        CPPUNIT_ASSERT_LESSEQUAL(new_y, energy_ball->y());
        cout << "OK";
    }

    void testCreateEast() {
        cout << endl << "TEST crear correctamente en direccion Este: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < config->getFps(); ++i) {
                world->step();
                CPPUNIT_ASSERT_EQUAL((EnergyBall*) nullptr, world->getEnergyBall(0));
            }
        for (int i = 0; i < config->getFps(); ++i)
            world->step(); // Step donde se crea EnergyBall

        float new_x = e_transm_x + dist_transm_to_enrgball;
        auto energy_ball = world->getEnergyBall(0);

        CPPUNIT_ASSERT_EQUAL((EnergyBall*) nullptr, world->getEnergyBall(1)); // No existe otra bola
        CPPUNIT_ASSERT_EQUAL(e_transm_y, energy_ball->y());
        CPPUNIT_ASSERT_GREATEREQUAL(new_x, energy_ball->x());
        cout << "OK";
    }

    void testCreateWest() {
        cout << endl << "TEST crear correctamente en direccion Oeste: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "O");
        world->createCollidable(data);
        for (int j = 1; j < TIME_TO_RELEASE; ++j)
            for (int i = 0; i < config->getFps(); ++i) {
                world->step();
                CPPUNIT_ASSERT_EQUAL((EnergyBall*) nullptr, world->getEnergyBall(0));
            }
        for (int i = 0; i < config->getFps(); ++i)
            world->step(); // Step donde se crea EnergyBall

        float new_x = e_transm_x - dist_transm_to_enrgball;
        auto energy_ball = world->getEnergyBall(0);
        CPPUNIT_ASSERT_EQUAL((EnergyBall*) nullptr, world->getEnergyBall(1)); // No existe otra bola
        CPPUNIT_ASSERT_EQUAL(e_transm_y, energy_ball->y());
        CPPUNIT_ASSERT_LESSEQUAL(new_x, energy_ball->x());
        cout << "OK";
    }

    void testCreateMoreThanOne() {
        cout << endl << "TEST crear mas de una bola de energia: ";

        size_t total_balls = 0;
        bool ball_removed = false;

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "O");
        world->createCollidable(data);
        for (int k = 0; k < 2; ++k) {
            for (int j = 1; j < TIME_TO_RELEASE; ++j) {
                for (int i = 0; i < config->getFps(); ++i)
                    world->step();
                if (total_balls > 0 && !world->getEnergyBall(k))
                    ball_removed = true; // Se elimino una bola por el tiempo transcurrido
            }
            for (int i = 0; i < config->getFps(); ++i)
                world->step(); // Step donde se crea EnergyBall
            if (world->getEnergyBall(k))
                ++total_balls;
        }
        CPPUNIT_ASSERT_EQUAL((size_t) 2, total_balls);
        CPPUNIT_ASSERT(ball_removed);
        cout << "OK";
    }

    void testMovesNorth() {
        cout << endl << "TEST moverse en direccion Norte: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "N");
        world->createCollidable(data);
        releaseEnergyBall();

        auto energy_ball = world->getEnergyBall(0);
        float previous_pos_y = energy_ball->y();
        float previous_pos_x = energy_ball->x();
        for (int i = 0; i < config->getFps(); ++i)
            world->step();  // Permito avanzar a la bola de energia

            CPPUNIT_ASSERT_GREATER(previous_pos_y, energy_ball->y());
        CPPUNIT_ASSERT_EQUAL(previous_pos_x, energy_ball->x());
        cout << "OK";
    }

    void testMovesSouth() {
        cout << endl << "TEST moverse en direccion Sur: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "S");
        world->createCollidable(data);
        releaseEnergyBall();

        auto energy_ball = world->getEnergyBall(0);
        float previous_pos_y = energy_ball->y();
        float previous_pos_x = energy_ball->x();
        for (int i = 0; i < config->getFps(); ++i)
            world->step(); // Permito avanzar a la bola de energia

        CPPUNIT_ASSERT_LESS(previous_pos_y, energy_ball->y());
        CPPUNIT_ASSERT_EQUAL(previous_pos_x, energy_ball->x());
        cout << "OK";
    }

    void testMovesEast() {
        cout << endl << "TEST moverse en direccion Este: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        releaseEnergyBall();

        auto energy_ball = world->getEnergyBall(0);
        float previous_pos_x = energy_ball->x();
        for (int i = 0; i < config->getFps(); ++i)
            world->step(); // Permito avanzar a la bola de energia

        float diff_y = energy_ball->y() - e_transm_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        CPPUNIT_ASSERT_GREATER(previous_pos_x, energy_ball->x());
        cout << "OK";
    }

    void testMovesWest() {
        cout << endl << "TEST moverse en direccion Oeste: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "O");
        world->createCollidable(data);
        releaseEnergyBall();

        auto energy_ball = world->getEnergyBall(0);
        float previous_pos_x = energy_ball->x();
        for (int i = 0; i < config->getFps(); ++i)
            world->step();  // Permito avanzar a la bola de energia

        float diff_y = energy_ball->y() - e_transm_y;
        CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        CPPUNIT_ASSERT_LESS(previous_pos_x, energy_ball->x());
        cout << "OK";
    }

    void testMovesNorthWithFixedSpeed() {
        cout << endl << "TEST moverse en direccion Norte con velocidad cte.: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "N");
        world->createCollidable(data);
        releaseEnergyBall();

        auto energy_ball = world->getEnergyBall(0);
        float y_step = 0;
        float init_y = energy_ball->y();
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            if (y_step == 0)
                y_step = energy_ball->y() - init_y;
            float diff_y = abs(y_step * i) - abs(energy_ball->y());
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        }
        cout << "OK";
    }

    void testMovesSouthWithFixedSpeed() {
        cout << endl << "TEST moverse en direccion Sur con velocidad cte.: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "S");
        world->createCollidable(data);
        releaseEnergyBall();

        auto energy_ball = world->getEnergyBall(0);
        float y_step = 0;
        float init_y = energy_ball->y();
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            if (y_step == 0)
                y_step = energy_ball->y() - init_y;
            float diff_y = abs(y_step * i) - abs(energy_ball->y());
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_y);
        }
        cout << "OK";
    }

    void testMovesEastWithFixedSpeed() {
        cout << endl << "TEST moverse en direccion Este con velocidad cte.: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        releaseEnergyBall();

        auto energy_ball = world->getEnergyBall(0);
        float x_step = 0;
        float init_x = energy_ball->x();
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            if (x_step == 0)
                x_step = energy_ball->x() - init_x;
            float diff_x = abs(x_step * i) - abs(energy_ball->x());
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x);
        }
        cout << "OK";
    }

    void testMovesWestWithFixedSpeed() {
        cout << endl << "TEST moverse en direccion Oeste con velocidad cte.: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        releaseEnergyBall();

        auto energy_ball = world->getEnergyBall(0);
        float x_step = 0;
        float init_x = energy_ball->x();
        for (int i = 0; i < config->getFps(); i++) {
            world->step();
            if (x_step == 0)
                x_step = energy_ball->x() - init_x;
            float diff_x = abs(x_step * i) - abs(energy_ball->x());
            CPPUNIT_ASSERT_LESS(DELTA_POS, diff_x);
        }
        cout << "OK";
    }

    void testDiesAfterLifetimeReached() {
        cout << endl << "TEST muere despues de cierto tiempo: ";

        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        releaseEnergyBall();

        int n_bodies = world->getWorld()->GetBodyCount();
        int iterations = ENERGY_BALL_MAX_LIFETIME / TIME_STEP;
        for (int i = 0; i < iterations; ++i)
            world->step(); // Step donde se crea EnergyBall
        // Testeo que se haya eliminado de world de Box2D
        CPPUNIT_ASSERT_LESS(n_bodies, world->getWorld()->GetBodyCount());
        cout << "OK";
    }

    void testTransmitterAddedToUpdateVectorAfterReleasingBall() {
        cout << endl << "TEST verificar que se agrega a vector de objetos aSctualizados luego de "
                        "crear bola energia: ";
        auto data = make_shared<EnergyTransmitterData>(e_transm_x, e_transm_y, "E");
        world->createCollidable(data);
        releaseEnergyBall();
        auto updated_transm = (EnergyTransmitter*) world->getObjectsToUpdate().at(0);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getObjectsToUpdate().size());
        // Verifico es transmisor correcto
        CPPUNIT_ASSERT_EQUAL((size_t) 0, updated_transm->id());
        CPPUNIT_ASSERT_EQUAL(O_E, updated_transm->getDirection());
        cout << "OK";
    }
};
#endif //PORTAL_TESTENERGYBALLANDENERGYTRANSMITTER_H
