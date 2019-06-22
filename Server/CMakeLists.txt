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
        CollidableData/BoxCreator.cpp CollidableData/BoxCreator.h
        Configuration.cpp Configuration.h
        Model/Shots/Shooter.cpp Model/Shots/Shooter.h
        CollidableData/YamlParser.cpp CollidableData/YamlParser.h
        CollidableData/Data/RockBlockData.cpp CollidableData/Data/RockBlockData.h
        CollidableData/Data/WorldData.cpp CollidableData/Data/WorldData.h
        CollidableData/Data/MetalBlockData.cpp CollidableData/Data/MetalBlockData.h
        CollidableData/Data/MetalDiagonalBlockData.cpp CollidableData/Data/MetalDiagonalBlockData.h
        CollidableData/Data//RockData.cpp CollidableData/Data/RockData.h
        CollidableData/Data/AcidData.cpp CollidableData/Data/AcidData.h
        CollidableData/Data/ButtonData.cpp CollidableData/Data/ButtonData.h
        CollidableData/Data/GateData.cpp CollidableData/Data/GateData.h
        CollidableData/Data/EnergyTransmitterData.cpp CollidableData/Data/EnergyTransmitterData.h
        CollidableData/Data/EnergyReceiverData.cpp CollidableData/Data/EnergyReceiverData.h
        CollidableData/Data/EnergyBarrierData.cpp CollidableData/Data/EnergyBarrierData.h
        CollidableData/Data/ChellData.cpp CollidableData/Data/ChellData.h
        CollidableData/Data/CakeData.cpp CollidableData/Data/CakeData.h
        CollidableData/CollidableData.h)

target_link_libraries(portal-src common-src Box2D yaml-cpp pthread)



