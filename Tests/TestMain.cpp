#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "TestWorld.h"
#include "TestChell.h"
#include "TestRock.h"
#include "TestButton.h"
#include "TestEnergyReceiver.h"
#include "TestYamlParser.h"
#include "TestGate.h"
#include "TestEnergyBallAndEnergyTransmitter.h"
#include "TestEnergyBallAndEnergyReceiver.h"
#include "TestEnergyBall.h"
#include "TestProtocolTranslator.h"
#include "TestPositionTranslator.h"
#include "TestWorldObjectDTOTranslator.h"
#include "TestCake.h"

//CPPUNIT_TEST_SUITE_REGISTRATION( TestYamlParser );
CPPUNIT_TEST_SUITE_REGISTRATION( TestProtocolTranslator );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestPositionTranslator );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestWorld );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestChell );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestRock );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestButton );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestGate );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestEnergyBallAndEnergyTransmitter );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestEnergyBallAndEnergyReceiver );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestEnergyReceiver );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestEnergyBall );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestWorldObjectDTOTranslator );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestCake );

using CppUnit::TestFactoryRegistry;

int main( int argc, char **argv) {
    CppUnit::TextUi::TestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();
    runner.addTest( registry.makeTest() );
    runner.run();
    return 0;
}
