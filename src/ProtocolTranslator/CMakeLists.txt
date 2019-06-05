cmake_minimum_required(VERSION 3.10)
project(Portal)

set(CMAKE_CXX_STANDARD 11)

add_library(protocol-translator
        ProtocolTranslator.cpp
        ProtocolDTO.h MoveLeftDTO.cpp MoveLeftDTO.h MoveRightDTO.cpp MoveRightDTO.h JumpDTO.cpp JumpDTO.h StopDTO.cpp StopDTO.h PortalDTO.cpp PortalDTO.h PinToolDTO.cpp PinToolDTO.h LiftRockDTO.cpp LiftRockDTO.h DropRockDTO.cpp DropRockDTO.h)
