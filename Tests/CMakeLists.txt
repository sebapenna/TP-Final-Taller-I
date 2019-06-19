cmake_minimum_required(VERSION 3.10)
project(Portal)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall  -Werror -pedantic -pedantic-errors" )

add_executable(tests
        TestMain.cpp
        CPPTests/TestWorld.h
        CPPTests/TestChell.h
        CPPTests/TestYamlParser.h
        CPPTests/TestRock.h
        CPPTests/TestButton.h
        CPPTests/TestGate.h
        CPPTests/TestEnergyReceiver.h
        CPPTests/TestEnergyBallAndEnergyTransmitter.h
        CPPTests/TestEnergyBallAndEnergyReceiver.h
        CPPTests/TestEnergyBall.h
        CPPTests/TestProtocolTranslator.h
        CPPTests/TestPositionTranslator.h CPPTests/TestWorldObjectDTOTranslator.h)

target_link_libraries(tests cppunit portal-src common-src)


add_executable(client
        ../Tests/ClientTest.cpp CPPTests/TestCake.h CPPTests/TestPortal.h)

target_link_libraries(client portal-src)