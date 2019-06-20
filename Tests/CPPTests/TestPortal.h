#ifndef PORTAL_TESTPORTAL_H
#define PORTAL_TESTPORTAL_H


#include <cppunit/extensions/HelperMacros.h>
#include "Server/Model/World.h"
#include "Server/Model/constants.h"
#include <Common/exceptions.h>
#include <string>

using std::cout;
using std::endl;

class TestPortal : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( TestPortal );
        CPPUNIT_TEST( testCreateOnMetalBlockLeftSide );
        CPPUNIT_TEST( testCreateOnMetalBlockRightSide );
        CPPUNIT_TEST( testCreateOnMetalBlockUpSide );
        CPPUNIT_TEST( testCreateOnMetalBlockDownSide );
        CPPUNIT_TEST( testDontCreateOnAcid );
        CPPUNIT_TEST( testDontCreateOnButton );
        CPPUNIT_TEST( testDontCreateOnEnergyReceiver );
        CPPUNIT_TEST( testDontCreateOnEnergyTransmitter );
        CPPUNIT_TEST( testDontCreateOnEnergyBarrier );
        CPPUNIT_TEST( testDontCreateOnRockBlock );
        CPPUNIT_TEST( testDontCreateOnRock );
        CPPUNIT_TEST( testDontCreateOnChellAndGoThroughIt );
        CPPUNIT_TEST( testDontCreateOnClosedGate );
        CPPUNIT_TEST( testDontCreateOnOpenGateAndGoThroughIt );
        CPPUNIT_TEST( testDontCreatePortalOnPortal );
        CPPUNIT_TEST( testCreateBlueAndOrangePortalForOneChell );
        CPPUNIT_TEST( testChangeOrangePortalForOneChell );
        CPPUNIT_TEST( testChangeBluePortalForOneChell );
        CPPUNIT_TEST( testTwoChellsCreatingPortals );
        CPPUNIT_TEST( testResetPortals );
    CPPUNIT_TEST_SUITE_END();

private:
    World *world;
    Chell *chell;
    size_t width = 100;
    size_t height = 200;
    float chell_x = 0;
    float chell_y = 2;

public:
    void setUp() {
        world = new World(width, height);
        world->createRockBlock(1000, 4, 0, -2);  // Piso
        world->createChell(chell_x, chell_y);
        chell = world->getChell(0);
    }

    void tearDown() {
        delete world;
    }

    void testCreateOnMetalBlockLeftSide() {
        cout << endl << endl << "TEST PORTAL";
        cout << endl << "TEST crear sobre cara izquierda bloque metal: ";
        float w = 4, h = 4, x = 20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getShootables().size());
        auto portal = (Portal*) world->getShootables().at(0);
        CPPUNIT_ASSERT_EQUAL(y, portal->y());
        CPPUNIT_ASSERT_EQUAL(BLUE_PORTAL, portal->colour());
        CPPUNIT_ASSERT_LESS(x, portal->x());
        cout << "OK";
    }

    void testCreateOnMetalBlockRightSide() {
        cout << endl << "TEST crear sobre cara derecha bloque metal: ";
        float w = 4, h = 4, x = -20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->shootPortal(0, -30, 2, ORANGE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getShootables().size());
        auto portal = (Portal*) world->getShootables().at(0);
        CPPUNIT_ASSERT_EQUAL(y, portal->y());
        CPPUNIT_ASSERT_EQUAL(ORANGE_PORTAL, portal->colour());
        CPPUNIT_ASSERT_GREATER(x, portal->x());
        cout << "OK";
    }

    void testCreateOnMetalBlockUpSide() {
        cout << endl << "TEST crear sobre cara superior bloque metal: ";
        float w = 4, h = 4, x = 0, y = 20;
        world->createMetalBlock(w, h, x, y);
        world->shootPortal(0, 0, 30, BLUE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getShootables().size());
        auto portal = (Portal*) world->getShootables().at(0);
        CPPUNIT_ASSERT_EQUAL(x, portal->x());
        CPPUNIT_ASSERT_LESS(y, portal->y());
        cout << "OK";
    }

    void testCreateOnMetalBlockDownSide() {
        cout << endl << "TEST crear sobre cara inferior bloque metal: ";
        float w = 4, h = 4, x = 0, y = 30;
        world->createChell(0, 50);  // Coloco chell en el aire para disparar debajo
        world->createMetalBlock(w, h, x, y);
        world->shootPortal(1, 0, -30, BLUE_PORTAL); // Chell 1 dispara
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getShootables().size());
        auto portal = (Portal*) world->getShootables().at(0);
        CPPUNIT_ASSERT_EQUAL(x, portal->x());
        CPPUNIT_ASSERT_GREATER(y, portal->y());
        cout << "OK";
    }

    void testDontCreateOnRockBlock() {
        cout << endl << "TEST no crear sobre bloque piedra ni atravesar: ";
        float w = 4, h = 4, x = 20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->createRockBlock(w, h, x - 10, y);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getShootables().size());
        cout << "OK";
    }

    void testDontCreateOnRock() {
        cout << endl << "TEST no crear sobre piedra ni atravesar: ";
        float w = 4, h = 4, x = 20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->createRock(x - 10, y);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getShootables().size());
        cout << "OK";
    }

    void testDontCreateOnAcid() {
        cout << endl << "TEST no crear sobre acido ni atravesar: ";
        float w = 4, h = 4, x = 20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->createAcid(x - 10, y);    // Hardcodeo acido vertical (irreal en juego)
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getShootables().size());
        cout << "OK";
    }

    void testDontCreateOnButton() {
        cout << endl << "TEST no crear sobre boton ni atravesar: ";
        float w = 4, h = 4, x = 20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->createButton(x - 10, y);  // Hardcodeo boton vertical (irreal en juego)
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getShootables().size());
        cout << "OK";
    }

    void testDontCreateOnEnergyReceiver() {
        cout << endl << "TEST no crear sobre receptor energia ni atravesar: ";
        float w = 4, h = 4, x = 20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->createEnergyReceiver(x - 10, y);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getShootables().size());
        cout << "OK";
    }

    void testDontCreateOnEnergyTransmitter() {
        cout << endl << "TEST no crear sobre transmisor energia ni atravesar: ";
        float w = 4, h = 4, x = 20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->createEnergyTransmitter(x - 10, y, O_E);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getShootables().size());
        cout << "OK";
    }

    void testDontCreateOnEnergyBarrier() {
        cout << endl << "TEST no crear sobre barrera energia ni atravesar: ";
        float w = 4, h = 4, x = 20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->createEnergyBarrier(x - 10, 4, O_V);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getShootables().size());
        cout << "OK";
    }

    void testDontCreateOnChellAndGoThroughIt() {
        cout << endl << "TEST no crear sobre barrera chell pero y crear atravesar: ";
        float w = 4, h = 4, x = 20, y = 2;
        float x2 = x - 10;
        world->createMetalBlock(w, h, x, y);
        world->createChell(x2, y);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getShootables().size());
        auto portal = (Portal*) world->getShootables().at(0);    // Se creo portal sobre bloque metal detras
        CPPUNIT_ASSERT_EQUAL(y, portal->y());
        CPPUNIT_ASSERT_GREATER(x2, portal->x());
        cout << "OK";
    }

    void testDontCreateOnClosedGate() {
        cout << endl << "TEST no crear sobre compuerta cerrada ni atravesar: ";
        float w = 4, h = 4, x = 20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->createButton(-100, y);  // Hardcodeo boton vertical (irreal en juego)
        world->createGate(x - 10, 4, {0}, {});
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getShootables().size());
        cout << "OK";
    }

    void testDontCreateOnOpenGateAndGoThroughIt() {
        cout << endl << "TEST no crear sobre compuerta abierta pero atravesar: ";
        float w = 4, h = 4, x = 20, y = 2;
        float x2 = x - 10;
        world->createMetalBlock(w, h, x, y);
        world->createButton(-100, y);  // Hardcodeo boton vertical (irreal en juego)
        world->createGate(x2, 4, {0}, {});
        auto button = world->getButton(0);
        button->activate();
        world->step();  // Permito se active button y abra gate
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        auto portal = (Portal*) world->getShootables().at(0);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getShootables().size());
        CPPUNIT_ASSERT_LESS(DELTA_POS, abs(y - portal->y()));
        CPPUNIT_ASSERT_GREATER(x2, portal->x());
        cout << "OK";
    }

    void testDontCreatePortalOnPortal() {
        cout << endl << "TEST no crear portal sobre otro portal: ";
        float w = 4, h = 4, x = 20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        world->shootPortal(0, 30, 2, ORANGE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 1, world->getShootables().size());
        auto portal = (Portal*) world->getShootables().at(0);
        CPPUNIT_ASSERT_EQUAL(y, portal->y());
        CPPUNIT_ASSERT_EQUAL(BLUE_PORTAL, portal->colour());
        CPPUNIT_ASSERT_LESS(x, portal->x());
        cout << "OK";
    }

    void testCreateBlueAndOrangePortalForOneChell() {
        cout << endl << "TEST crear portal azul y naranja: ";
        float w = 4, h = 4, x = 20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->createMetalBlock(w, h, -1 * x, y);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        world->shootPortal(0, -30, 2, ORANGE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 2, world->getShootables().size());
        auto blue_portal = (Portal*) world->getShootables().at(0);
        auto orange_portal = (Portal*) world->getShootables().at(1);

        CPPUNIT_ASSERT_EQUAL(y, blue_portal->y());
        CPPUNIT_ASSERT_EQUAL(BLUE_PORTAL, blue_portal->colour());
        CPPUNIT_ASSERT_LESS(x, blue_portal->x());

        CPPUNIT_ASSERT_EQUAL(y, orange_portal->y());
        CPPUNIT_ASSERT_EQUAL(ORANGE_PORTAL, orange_portal->colour());
        CPPUNIT_ASSERT_GREATER(-1 * x, orange_portal->x());
        cout << "OK";
    }

    void testChangeOrangePortalForOneChell() {
        cout << endl << "TEST cambiar portal naranja: ";
        float w = 4, h = 4, x = 20, y = 2;
        float x2 = x - 10;
        world->createMetalBlock(w, h, x, y);
        world->createMetalBlock(w, h, -1 * x, y);
        world->createMetalBlock(w, h, chell_x, 20);
        world->createMetalBlock(w, h, 20, 20);

        world->createChell(x2, y);
        world->shootPortal(0, chell_x, 30, ORANGE_PORTAL);
        world->shootPortal(1, -30, 2, ORANGE_PORTAL);

        world->step();

        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        world->shootPortal(0, 20, 18, ORANGE_PORTAL);   // Disparo caiga debajo del bloque

        world->step();  // En step se eliminan portales viejos

        CPPUNIT_ASSERT_EQUAL((size_t) 3, world->getShootables().size());
        auto orange_portal = (Portal*) world->getShootables().at(3); // Nuevo portal tiene id 2
        auto other_chell_portal = (Portal*) world->getShootables().at(1);


        CPPUNIT_ASSERT_GREATER(chell_y, orange_portal->y());
        CPPUNIT_ASSERT_LESS((float) 20, orange_portal->y());
        CPPUNIT_ASSERT_EQUAL(ORANGE_PORTAL, orange_portal->colour());
        CPPUNIT_ASSERT_EQUAL(ORANGE_PORTAL, other_chell_portal->colour());
        CPPUNIT_ASSERT_EQUAL((float) 20, orange_portal->x());
        cout << "OK";
    }

    void testChangeBluePortalForOneChell() {
        cout << endl << "TEST cambiar portal azul: ";
        float w = 4, h = 4, x = 20, y = 2;
        float x2 = x - 10;
        world->createMetalBlock(w, h, x, y);
        world->createMetalBlock(w, h, -1 * x, y);
        world->createMetalBlock(w, h, chell_x, 20);
        world->createMetalBlock(w, h, 20, 20);

        world->createChell(x2, y);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        world->shootPortal(1, chell_x, 20, BLUE_PORTAL);
        world->shootPortal(0, -30, 2, ORANGE_PORTAL);

        world->step();

        world->shootPortal(0, 20, 18, BLUE_PORTAL); // Disparo caiga debajo del bloque

        world->step();  // En step se eliminan portales viejos

        CPPUNIT_ASSERT_EQUAL((size_t) 3, world->getShootables().size());
        auto blue_portal = (Portal*) world->getShootables().at(3); // Nuevo portal tiene id 2
        auto other_chell_portal = (Portal*) world->getShootables().at(1);

        CPPUNIT_ASSERT_GREATER(chell_y, blue_portal->y());
        CPPUNIT_ASSERT_LESS((float) 20, blue_portal->y());
        CPPUNIT_ASSERT_EQUAL(BLUE_PORTAL, blue_portal->colour());
        CPPUNIT_ASSERT_EQUAL(BLUE_PORTAL, other_chell_portal->colour());
        CPPUNIT_ASSERT_EQUAL((float) 20, blue_portal->x());
        cout << "OK";
    }

    void testTwoChellsCreatingPortals() {
        cout << endl << "TEST mas de una chell creando portal: ";
        float w = 4, h = 4, x = 20, y = 2;
        float x2 = x - 10;
        world->createMetalBlock(w, h, x, y);
        world->createMetalBlock(w, h, -1 * x, y);
        world->createChell(x2, y);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        world->shootPortal(1, -30, 2, BLUE_PORTAL);
        CPPUNIT_ASSERT_EQUAL((size_t) 2, world->getShootables().size());
        auto portal1 = (Portal*) world->getShootables().at(0);
        auto portal2 = (Portal*) world->getShootables().at(0);
        CPPUNIT_ASSERT_EQUAL(BLUE_PORTAL, portal1->colour());
        CPPUNIT_ASSERT_EQUAL(BLUE_PORTAL, portal2->colour());
        cout << "OK";
    }

    void testResetPortals() {
        cout << endl << "TEST resetear portales de chell: ";
        float w = 4, h = 4, x = 20, y = 2;
        world->createMetalBlock(w, h, x, y);
        world->createMetalBlock(w, h, -1 * x, y);
        world->shootPortal(0, 30, 2, BLUE_PORTAL);
        world->shootPortal(0, -30, 2, ORANGE_PORTAL);

        world->step();
        world->resetPortals(0); // Reseteo portales
        world->step();  // Se eliminan en step

        CPPUNIT_ASSERT_EQUAL((size_t) 0, world->getShootables().size());
        cout << "OK";
    }

};


#endif //PORTAL_TESTPORTAL_H
