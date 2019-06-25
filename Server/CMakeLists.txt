cmake_minimum_required(VERSION 3.10)
project(Portal)

include_directories(..)

add_library(portal-src
        Model/Chell.cpp
        Model/ContactListener.cpp
        Model/constants.h
        Model/EnergyBall.cpp
        ../Common/exceptions.h
        Model/Shots/Portal.cpp
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
        Model/Shots/PinTool.cpp
        DTOProcessor.cpp DTOProcessor.h
        ServerMain.cpp
        Lobby.cpp Lobby.h
        GameThread.cpp GameThread.h
        Player.cpp Player.h
        WorldObjectDTOTranslator.cpp WorldObjectDTOTranslator.h
        PositionTranslator.cpp PositionTranslator.h
        Event.cpp Event.h
        ../Common/HandshakeHandler.cpp ../Common/HandshakeHandler.h
        Model/Obstacles/Cake.cpp Model/Obstacles/Cake.h
        Model/RayCastCallback.cpp Model/RayCastCallback.h
        Model/BodyCreator.cpp Model/BodyCreator.h
        Configuration.cpp Configuration.h
        Model/Shots/Shooter.cpp Model/Shots/Shooter.h
        Model/CollidableData/YamlParser.cpp Model/CollidableData/YamlParser.h
        Model/CollidableData/Data/RockBlockData.cpp Model/CollidableData/Data/RockBlockData.h
        Model/CollidableData/Data/WorldData.cpp Model/CollidableData/Data/WorldData.h
        Model/CollidableData/Data/MetalBlockData.cpp Model/CollidableData/Data/MetalBlockData.h
        Model/CollidableData/Data/MetalDiagonalBlockData.cpp Model/CollidableData/Data/MetalDiagonalBlockData.h
        Model/CollidableData/Data//RockData.cpp Model/CollidableData/Data/RockData.h
        Model/CollidableData/Data/AcidData.cpp Model/CollidableData/Data/AcidData.h
        Model/CollidableData/Data/ButtonData.cpp Model/CollidableData/Data/ButtonData.h
        Model/CollidableData/Data/GateData.cpp Model/CollidableData/Data/GateData.h
        Model/CollidableData/Data/EnergyTransmitterData.cpp Model/CollidableData/Data/EnergyTransmitterData.h
        Model/CollidableData/Data/EnergyReceiverData.cpp Model/CollidableData/Data/EnergyReceiverData.h
        Model/CollidableData/Data/EnergyBarrierData.cpp Model/CollidableData/Data/EnergyBarrierData.h
        Model/CollidableData/Data/ChellData.cpp Model/CollidableData/Data/ChellData.h
        Model/CollidableData/Data/CakeData.cpp Model/CollidableData/Data/CakeData.h
        Model/CollidableData/CollidableData.h)

target_link_libraries(portal-src common-src Box2D yaml-cpp pthread)



