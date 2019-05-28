cmake_minimum_required(VERSION 3.10)
project(Portal)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall  -Werror -pedantic -pedantic-errors" )

add_executable(tests
        TestMain.cpp
        TestStage.h
#        ../src/Game.cpp
#        ../src/Stage.cpp
        TestChell.h
#        ../src/Chell.cpp
#        ../src/ContactListener.cpp
#        ../src/exceptions.h
        TestYamlParser.h)

target_link_libraries(tests cppunit portal-src)
