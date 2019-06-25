cmake_minimum_required(VERSION 3.10)
project(Portal)

#SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -g -DDEBUG_MODE" )
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -g" )

include_directories(${PROJECT_SOURCE_DIR})

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" OFF)
option(BOX2D_BUILD_STATIC "Build Box2D static libraries" ON)
set(BOX2D_VERSION 2.3.0)


set(project_ui
        client/GUILogin/mainwindow.ui)

set(project_headers
        client/GUILogin/mainwindow.h
        client/GUILogin/GUIReceiver.h
        )

set(project_sources
        client/GUILogin/mainwindow.cpp
        client/GUILogin/GUIReceiver.cpp
        client/main.cpp
        )

qt5_wrap_ui(project_headers_wrapped ${project_ui})
qt5_wrap_cpp(project_sources_moc ${project_headers})

add_subdirectory(Box2D)
add_subdirectory(Yaml)
include_directories(Yaml/include)   # Habilita la carpeta include de Yaml
add_subdirectory(Common)
add_subdirectory(Server)
add_subdirectory(Tests)
add_subdirectory(client)
include_directories(${PROJECT_BINARY_DIR})

file(COPY Server/Config DESTINATION ./)
file(COPY client/assets DESTINATION ./)
file(COPY Server/Config DESTINATION ./Tests)    # Archivos disponibles para tests
file(COPY Tests/CPPTests/test.yaml DESTINATION ./Tests)   # Archivo yaml para tests

add_executable (portal_client
        ${project_headers}
        ${project_sources}
        ${project_sources_moc}
        ${project_headers_wrapped})

target_link_libraries(portal_client
        sdldemo portal-src common-src
        SDL2 SDL2_image
        pthread SDL2_mixer
        SDL2_ttf Qt5::Core
        Qt5::Gui Qt5::Widgets)

add_executable(portal_server Server/ServerMain.cpp)
target_link_libraries(portal_server portal-src)



message("[INFO] Adding Installation directives")
INSTALL(TARGETS portal_client portal_server DESTINATION /usr/bin)
INSTALL(DIRECTORY client/assets DESTINATION /var/Portal)
INSTALL(DIRECTORY Server/Config DESTINATION /var/Portal)
INSTALL(DIRECTORY Server/Config DESTINATION /etc/Portal)
INSTALL(FILES Server/Config/test.yaml DESTINATION /etc/Portal/Server/Config)




