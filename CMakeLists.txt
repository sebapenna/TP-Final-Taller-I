cmake_minimum_required(VERSION 3.10)
project(Portal)

# todo CMAKE FULL
#SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -DDEBUG_MODE" )
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories(${PROJECT_SOURCE_DIR})

option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" OFF)
option(BOX2D_BUILD_STATIC "Build Box2D static libraries" ON)
set(BOX2D_VERSION 2.3.0)
set(LIB_INSTALL_DIR lib${LIB_SUFFIX})

set(YAML_CPP_BUILD_TESTS OFF)
set(YAML_CPP_BUILD_TOOLS OFF)
set(YAML_CPP_BUILD_CONTRIB OFF)
set(YAML_CPP_BUILD_INSTALL OFF)

add_subdirectory(Box2D)
add_subdirectory(Yaml)
include_directories(Yaml/include)   # Habilita la carpeta include de Yaml
add_subdirectory(Common)
add_subdirectory(Server)
add_subdirectory(Tests)
add_subdirectory(client)
