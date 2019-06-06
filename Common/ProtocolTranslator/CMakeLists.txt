cmake_minimum_required(VERSION 3.10)
project(Portal)

set(CMAKE_CXX_STANDARD 11)

add_library(protocol-translator
        ProtocolTranslator.cpp
        ProtocolTranslator.h
        MoveLeftDTO.cpp
        MoveRightDTO.cpp
        JumpDTO.cpp
        StopDTO.cpp
        ShootPortalDTO.cpp
        ShootPinToolDTO.cpp
        LiftRockDTO.cpp
        DropRockDTO.cpp
        PlayerChellIdDTO.cpp
        )


