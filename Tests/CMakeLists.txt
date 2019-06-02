cmake_minimum_required(VERSION 3.10)
project(Portal)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall  -Werror -pedantic -pedantic-errors" )

add_executable(tests
        TestMain.cpp
        TestWorld.h
        TestChell.h
        TestYamlParser.h
        TestRock.h
        TestButton.h
        TestGate.h
        TestEnergyReceiver.h
        TestEnergyBallAndEnergyTransmitter.h)

target_link_libraries(tests cppunit portal-src)
