#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "TestStage.h"
#include "TestChell.h"
#include "TestYamlParser.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TestStage );
CPPUNIT_TEST_SUITE_REGISTRATION( TestChell );
CPPUNIT_TEST_SUITE_REGISTRATION( TestYamlParser );

using CppUnit::TestFactoryRegistry;

int main( int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();
    runner.addTest( registry.makeTest() );
    runner.run();
    return 0;
}