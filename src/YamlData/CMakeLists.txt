cmake_minimum_required(VERSION 3.10)
project(Portal)

set(CMAKE_CXX_STANDARD 11)

add_library(yaml-parser
        RockBlockData.cpp
        RockBlockData.h
        StageData.cpp
        StageData.h
        YamlParser.cpp
        YamlParser.h
        MetalBlockData.cpp MetalBlockData.h MetalDiagonalBlockData.cpp MetalDiagonalBlockData.h RockData.cpp RockData.h AcidData.cpp AcidData.h ButtonData.cpp ButtonData.h GateData.cpp GateData.h)

target_link_libraries(yaml-parser yaml-cpp)
