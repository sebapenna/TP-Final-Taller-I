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

CPPUNIT_TEST_SUITE_REGISTRATION( TestYamlParser );
CPPUNIT_TEST_SUITE_REGISTRATION( TestWorld );
CPPUNIT_TEST_SUITE_REGISTRATION( TestChell );
CPPUNIT_TEST_SUITE_REGISTRATION( TestRock );
CPPUNIT_TEST_SUITE_REGISTRATION( TestButton );
CPPUNIT_TEST_SUITE_REGISTRATION( TestEnergyReceiver );
CPPUNIT_TEST_SUITE_REGISTRATION( TestGate );
CPPUNIT_TEST_SUITE_REGISTRATION( TestEnergyBallAndEnergyTransmitter );

using CppUnit::TestFactoryRegistry;

int main( int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();
    runner.addTest( registry.makeTest() );
    runner.run();
    return 0;
}
