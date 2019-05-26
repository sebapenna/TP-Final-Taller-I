cmake_minimum_required(VERSION 3.10)
project(Portal)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories(..)

add_library(portal_src
        chell.cpp
        contact_listener.cpp
        constants.h
        energy_ball.cpp
        exceptions.h
        portal.cpp
        stage.cpp
        EnergyBlocks/energy_receiver.cpp
        EnergyBlocks/energy_transmitter.cpp
        GroundBlocks/block.cpp
        GroundBlocks/metal_block.cpp
        GroundBlocks/metal_diagonal_block.cpp
        GroundBlocks/rock_block.cpp
        Obstacles/acid.cpp
        Obstacles/button.cpp
        Obstacles/gate.cpp
        Obstacles/obstacle.h
        Obstacles/rock.cpp
        )

#link_directories(portal_src Box2D yaml-cpp)
