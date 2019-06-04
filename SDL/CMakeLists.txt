cmake_minimum_required(VERSION 2.8)
SET(CMAKE_BUILD_TYPE Debug)
project(sdl)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(sdldemo
  Renderer.cpp
        SDLException.cpp
  Window.cpp
        Sprite.cpp
        Sprite.h
        AnimatedSprite.cpp
        AnimatedSprite.h
        ChellAnimationView.cpp
        ChellAnimationView.h TextureFactory.cpp TextureFactory.h SpriteFactory.cpp SpriteFactory.h WorldView.cpp WorldView.h View.cpp View.h Camera.cpp Camera.h BlockViewMetal.cpp BlockViewMetal.h BlockViewRock.cpp BlockViewRock.h)


# Agrego la carpeta con los headers autogenerados a los includes
#message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
#include_directories(${PROJECT_BINARY_DIR})

add_executable (sdl-hello
  main.cpp  
)



target_link_libraries(sdl-hello sdldemo SDL2 SDL2_image)

#install(FILES assets/cat.gif DESTINATION ${CMAKE_BINARY_DIR})
