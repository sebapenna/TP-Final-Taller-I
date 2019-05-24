cmake_minimum_required(VERSION 3.10)
project(Portal)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall  -Werror -pedantic -pedantic-errors" )


add_executable(tests
        test_main.cpp
        test_stage.h
        ../src/stage.cpp
        test_chell.h
        ../src/chell.cpp
        ../src/contact_listener.cpp
        ../src/exceptions.h)

target_link_libraries(tests cppunit Box2D)

