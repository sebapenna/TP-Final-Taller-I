#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "Tests/CPPTests/TestWorld.h"
#include "Tests/CPPTests/TestChell.h"
#include "Tests/CPPTests/TestRock.h"
#include "Tests/CPPTests/TestButton.h"
#include "Tests/CPPTests/TestEnergyReceiver.h"
#include "Tests/CPPTests/TestYamlParser.h"
#include "Tests/CPPTests/TestGate.h"
#include "Tests/CPPTests/TestEnergyBallAndEnergyTransmitter.h"
#include "Tests/CPPTests/TestEnergyBallAndEnergyReceiver.h"
#include "Tests/CPPTests/TestEnergyBall.h"
#include "Tests/CPPTests/TestProtocolTranslator.h"
#include "Tests/CPPTests/TestPositionTranslator.h"
#include "Tests/CPPTests/TestWorldObjectDTOTranslator.h"
#include "Tests/CPPTests/TestCake.h"
#include "Tests/CPPTests/TestPortal.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TestYamlParser );
CPPUNIT_TEST_SUITE_REGISTRATION( TestProtocolTranslator );
CPPUNIT_TEST_SUITE_REGISTRATION( TestPositionTranslator );
CPPUNIT_TEST_SUITE_REGISTRATION( TestWorld );
CPPUNIT_TEST_SUITE_REGISTRATION( TestChell );
CPPUNIT_TEST_SUITE_REGISTRATION( TestRock );
CPPUNIT_TEST_SUITE_REGISTRATION( TestButton );
CPPUNIT_TEST_SUITE_REGISTRATION( TestGate );
CPPUNIT_TEST_SUITE_REGISTRATION( TestEnergyBallAndEnergyTransmitter );
CPPUNIT_TEST_SUITE_REGISTRATION( TestEnergyBallAndEnergyReceiver );
CPPUNIT_TEST_SUITE_REGISTRATION( TestEnergyReceiver );
CPPUNIT_TEST_SUITE_REGISTRATION( TestEnergyBall );
CPPUNIT_TEST_SUITE_REGISTRATION( TestWorldObjectDTOTranslator );
CPPUNIT_TEST_SUITE_REGISTRATION( TestCake );
CPPUNIT_TEST_SUITE_REGISTRATION( TestPortal );


using CppUnit::TestFactoryRegistry;

int main( int argc, char **argv) {
    CppUnit::TextUi::TestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();
    runner.addTest( registry.makeTest() );
    runner.run();
    return 0;
}
