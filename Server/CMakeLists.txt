cmake_minimum_required(VERSION 3.10)
project(Portal)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories(..)
add_subdirectory(YamlData)

add_library(portal-src
        Model/Chell.cpp
        Model/ContactListener.cpp
        Model/constants.h
        Model/EnergyBall.cpp
        ../Common/exceptions.h
        Model/Portal.cpp
        Model/World.cpp
        Model/EnergyBlocks/EnergyReceiver.cpp
        Model/EnergyBlocks/EnergyTransmitter.cpp
        Model/GroundBlocks/MetalBlock.cpp
        Model/GroundBlocks/MetalDiagonalBlock.cpp
        Model/GroundBlocks/RockBlock.cpp
        Model/Obstacles/Button.cpp
        Model/Obstacles/Gate.cpp
        Model/Obstacles/Rock.cpp
        Stage.cpp
        Model/Collidable.h
        Model/Obstacles/Acid.cpp
        Model/Obstacles/EnergyBarrier.cpp
        Model/PinTool.cpp
        DTOProcessor.cpp DTOProcessor.h
        ServerMain.cpp
        Lobby.cpp Lobby.h
        GameThread.cpp GameThread.h
        Player.cpp Player.h
        ReceiverThread.cpp ReceiverThread.h
        Model/WorldObjectsStorage.cpp Model/WorldObjectsStorage.h
        WorldObjectDTOTranslator.cpp WorldObjectDTOTranslator.h
        PositionTranslator.cpp PositionTranslator.h
        Event.cpp Event.h)

target_link_libraries(portal-src common-src Box2D yaml-parser pthread)


add_executable(server
        ServerMain.cpp)

target_link_libraries(server portal-src)

# todo : eliminar client test
add_executable(client
        ClientTest.cpp)

target_link_libraries(client portal-src)