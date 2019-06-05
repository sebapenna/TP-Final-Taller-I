cmake_minimum_required(VERSION 3.10)
project(Portal)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories(..)
add_subdirectory(YamlData)
add_subdirectory(ProtocolTranslator)

add_library(portal-src
        Chell.cpp
        ContactListener.cpp
        constants.h
        EnergyBall.cpp
        exceptions.h
        Portal.cpp
        World.cpp
        EnergyBlocks/EnergyReceiver.cpp
        EnergyBlocks/EnergyTransmitter.cpp
        GroundBlocks/MetalBlock.cpp
        GroundBlocks/MetalDiagonalBlock.cpp
        GroundBlocks/RockBlock.cpp
        Obstacles/Button.cpp
        Obstacles/Gate.cpp
        Obstacles/Rock.cpp
        Stage.cpp
        Collidable.h
        Obstacles/Acid.cpp
        Obstacles/EnergyBarrier.cpp
        PinTool.cpp
        protocol_macros.h)

target_link_libraries(portal-src Box2D yaml-parser protocol-translator
        resources)
