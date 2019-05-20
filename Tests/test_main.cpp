#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "test_1.h"

CPPUNIT_TEST_SUITE_REGISTRATION( FirstTest );

using CppUnit::TestFactoryRegistry;

int main( int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();
    runner.addTest( registry.makeTest() );
    runner.run();
    return 0;
}
