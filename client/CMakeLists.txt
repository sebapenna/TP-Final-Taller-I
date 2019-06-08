cmake_minimum_required(VERSION 2.8)
SET(CMAKE_BUILD_TYPE Debug)
project(Portal)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(..)
add_library(sdldemo
        ComponentsSDL/Renderer.cpp
        ComponentsSDL/SDLException.cpp
        ComponentsSDL/Window.cpp
        ComponentsSDL/Sprite.cpp
        ComponentsSDL/Sprite.h
        ComponentsSDL/AnimatedSprite.cpp
        ComponentsSDL/AnimatedSprite.h
        View/ChellAnimationView.cpp
        View/ChellAnimationView.h
        TextureFactory.cpp
        TextureFactory.h
        WorldView.cpp
        WorldView.h View/View.cpp
        View/View.h ComponentsSDL/Camera.cpp
        ComponentsSDL/Camera.h
        View/BlockViewMetal.cpp
        View/BlockViewMetal.h
        View/BlockViewRock.cpp
        View/BlockViewRock.h
        ComponentsSDL/Position.cpp
        ComponentsSDL/Position.h
        SDL_Runner.cpp
        SDL_Runner.h
        FakeServer.cpp
        FakeServer.h
        )



# Agrego la carpeta con los headers autogenerados a los includes
#message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
#include_directories(${PROJECT_BINARY_DIR})

add_executable (sdl-hello
  main.cpp  
)



target_link_libraries(sdl-hello common-src sdldemo SDL2 SDL2_image pthread)

#install(FILES assets/cat.gif DESTINATION ${CMAKE_BINARY_DIR})
