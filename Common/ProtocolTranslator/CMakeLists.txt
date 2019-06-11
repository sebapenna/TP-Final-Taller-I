cmake_minimum_required(VERSION 3.10)
project(Portal)

set(CMAKE_CXX_STANDARD 11)

add_library(protocol-translator
        ProtocolTranslator.cpp ProtocolTranslator.h
        MoveLeftDTO.cpp
        MoveRightDTO.cpp
        JumpDTO.cpp
        StopDTO.cpp
        ShootPortalDTO.cpp
        ShootPinToolDTO.cpp
        LiftRockDTO.cpp
        DropRockDTO.cpp
        PlayerChellIdDTO.cpp
        RockBlockDTO.cpp RockBlockDTO.h
        MetalBlockDTO.cpp MetalBlockDTO.h
        MetalDiagonalBlockDTO.cpp MetalDiagonalBlockDTO.h
        EnergyTransmitterDTO.cpp EnergyTransmitterDTO.h
        EnergyReceiverDTO.cpp EnergyReceiverDTO.h
        AcidDTO.cpp AcidDTO.h
        ButtonDTO.cpp ButtonDTO.h
        GateDTO.cpp GateDTO.h
        EnergyBarrierDTO.cpp EnergyBarrierDTO.h
        RockDTO.cpp RockDTO.h
        EnergyBallDTO.cpp EnergyBallDTO.h
        PortalDTO.cpp PortalDTO.h
        PinToolDTO.cpp PinToolDTO.h
        ChellDTO.cpp ChellDTO.h
        ButtonStateDTO.cpp ButtonStateDTO.h
        EnergyTransmitterActivateDTO.cpp EnergyTransmitterActivateDTO.h
        EnergyReceiverActivateDTO.cpp EnergyReceiverActivateDTO.h
        GateStateDTO.cpp GateStateDTO.h
        ConnectionDTO/QuitDTO.cpp ConnectionDTO/QuitDTO.h ConnectionDTO/BeginDTO.cpp ConnectionDTO/BeginDTO.h)


