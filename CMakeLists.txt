cmake_minimum_required(VERSION 3.10)
project(Portal)

# todo CMAKE FULL
#SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -DDEBUG_MODE" )
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -g -DDEBUG_MODE" )
# todo: borrar debug mode en la entrega !
include_directories(${PROJECT_SOURCE_DIR})

option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" OFF)
option(BOX2D_BUILD_STATIC "Build Box2D static libraries" ON)
set(BOX2D_VERSION 2.3.0)
#set(LIB_INSTALL_DIR lib${LIB_SUFFIX})

add_subdirectory(Box2D)
add_subdirectory(Yaml)
include_directories(Yaml/include)   # Habilita la carpeta include de Yaml
add_subdirectory(Common)
add_subdirectory(Server)
add_subdirectory(Tests)
add_subdirectory(client)


file(COPY Server/Config DESTINATION ./)
file(COPY client/assets DESTINATION ./)
file(COPY Tests/test.yaml DESTINATION ./)   # Archivo yaml para tests
#file(COPY client/assets DESTINATION ./)
## EJEMPLOS DE COPIA DE ARCHIVOS LOCALES
#file(COPY assets DESTINATION ./)
#file(COPY serverConfig.yaml DESTINATION ./)
#file(COPY defaultWeapons.yaml DESTINATION ./)
#file(COPY res DESTINATION ./)

#message("[INFO] Adding Installation directives")
#INSTALL(TARGETS worms_client worms_server worms_editor DESTINATION /usr/bin)
#INSTALL(DIRECTORY assets DESTINATION /var/Worms)
#INSTALL(DIRECTORY res DESTINATION /var/Worms)
#INSTALL(FILES defaultWeapons.yaml serverConfig.yaml DESTINATION /etc/Worms)

#file(COPY Server)

add_executable (client_sdl client/main.cpp)
target_link_libraries(client_sdl sdldemo portal-src common-src SDL2 SDL2_image pthread SDL2_mixer)

add_executable(server Server/ServerMain.cpp)
target_link_libraries(server portal-src)

