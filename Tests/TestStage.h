#ifndef PORTAL_TESTSTAGE_H
#define PORTAL_TESTSTAGE_H

#include <cppunit/extensions/HelperMacros.h>
#include "../Box2D/Box2D.h"
#include "src/Stage.h"

using std::cout;
using std::endl;

class TestStage : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( TestStage );
        CPPUNIT_TEST( testFixedWidthAndHeight );
    CPPUNIT_TEST_SUITE_END();

private:
    Stage *stage;
    size_t width = 20;
    size_t height = 30;

public:
    void setUp() {
        stage = new Stage(width, height);
    }

    void tearDown() {
        delete stage;
    }

    void testFixedWidthAndHeight() {
        cout << endl << "TEST ancho y alto de escenario fijo: ";
        stage->step();
        CPPUNIT_ASSERT_EQUAL(stage->getHeight(), height);
        CPPUNIT_ASSERT_EQUAL(stage->getWidth(), width);
        cout << "OK";
    }


};

#endif //PORTAL_TESTSTAGE_H
