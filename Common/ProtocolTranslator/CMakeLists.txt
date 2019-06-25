cmake_minimum_required(VERSION 3.10)
project(Portal)

set(CMAKE_CXX_STANDARD 11)

add_library(protocol-translator
        ProtocolTranslator.cpp ProtocolTranslator.h
        PlayerActionsDTO/MoveLeftDTO.cpp
        PlayerActionsDTO/MoveRightDTO.cpp
        PlayerActionsDTO/JumpDTO.cpp
        PlayerActionsDTO/StopDTO.cpp
        PlayerActionsDTO/ShootPortalDTO.cpp
        PlayerActionsDTO/ShootPinToolDTO.cpp
        PlayerActionsDTO/LiftRockDTO.cpp
        PlayerActionsDTO/DropRockDTO.cpp
        DataDTO/PlayerChellIdDTO.cpp
        DataDTO/RockBlockDTO.cpp DataDTO/RockBlockDTO.h
        DataDTO/MetalBlockDTO.cpp DataDTO/MetalBlockDTO.h
        DataDTO/MetalDiagonalBlockDTO.cpp DataDTO/MetalDiagonalBlockDTO.h
        DataDTO/EnergyTransmitterDTO.cpp DataDTO/EnergyTransmitterDTO.h
        DataDTO/EnergyReceiverDTO.cpp DataDTO/EnergyReceiverDTO.h
        DataDTO/AcidDTO.cpp DataDTO/AcidDTO.h
        DataDTO/ButtonDTO.cpp DataDTO/ButtonDTO.h
        DataDTO/GateDTO.cpp DataDTO/GateDTO.h
        DataDTO/EnergyBarrierDTO.cpp DataDTO/EnergyBarrierDTO.h
        DataDTO/RockDTO.cpp DataDTO/RockDTO.h
        DataDTO/EnergyBallDTO.cpp DataDTO/EnergyBallDTO.h
        DataDTO/PortalDTO.cpp DataDTO/PortalDTO.h
        DataDTO/PinToolDTO.cpp DataDTO/PinToolDTO.h
        DataDTO/ChellDTO.cpp DataDTO/ChellDTO.h
        DataDTO/ButtonStateDTO.cpp DataDTO/ButtonStateDTO.h
        DataDTO/EnergyTransmitterActivateDTO.cpp DataDTO/EnergyTransmitterActivateDTO.h
        DataDTO/EnergyReceiverActivateDTO.cpp DataDTO/EnergyReceiverActivateDTO.h
        DataDTO/GateStateDTO.cpp DataDTO/GateStateDTO.h
        GameStateDTO/QuitDTO.cpp GameStateDTO/QuitDTO.h
        GameStateDTO/BeginDTO.cpp GameStateDTO/BeginDTO.h
        DataDTO/CakeDTO.cpp DataDTO/CakeDTO.h
        PlayerActionsDTO/CommitSuicideDTO.cpp PlayerActionsDTO/CommitSuicideDTO.h
        PlayerActionsDTO/KillMissingChellDTO.cpp PlayerActionsDTO/KillMissingChellDTO.h
        PlayerActionsDTO/ResetPortalsDTO.cpp PlayerActionsDTO/ResetPortalsDTO.h
        DataDTO/WinnerDTO.cpp DataDTO/WinnerDTO.h)


