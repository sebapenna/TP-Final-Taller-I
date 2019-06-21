cmake_minimum_required(VERSION 2.8)
SET(CMAKE_BUILD_TYPE Debug)
project(Portal)

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
        View/BlockMetalView.cpp
        View/BlockMetalView.h
        View/BlockRockView.cpp
        View/BlockRockView.h
        ComponentsSDL/Position.cpp
        ComponentsSDL/Position.h
        SDL_Runner.cpp
        SDL_Runner.h
        FakeServer.cpp
        FakeServer.h
        View/DiagonalBlockMetalView.cpp
        View/DiagonalBlockMetalView.h
        View/AcidView.cpp
        View/AcidView.h
        View/RockView.cpp
        View/RockView.h
        View/GateView.cpp
        View/GateView.h
        View/EnergyBarrierView.cpp
        View/EnergyBarrierView.h
        View/BallView.cpp
        View/BallView.h
        View/ButtonView.cpp
        View/ButtonView.h
        ClientSender.cpp
        ClientSender.h
        ClientReceiver.cpp
        ClientReceiver.h
        View/BackgroundView.cpp
        View/BackgroundView.h
        View/EnergyTransmitterView.cpp
        View/EnergyTransmitterView.h
        View/EnergyReceiverView.cpp
        View/EnergyReceiverView.h
        ComponentsSDL/MusicPlayer.cpp
        ComponentsSDL/MusicPlayer.h
        CommandSender.cpp
        CommandSender.h
        CommandReceiver.cpp
        CommandReceiver.h View/CakeView.cpp View/CakeView.h View/EnergyBallView.cpp View/EnergyBallView.h View/PortalBlueView.cpp View/PortalBlueView.h View/PortalOrangeView.cpp View/PortalOrangeView.h View/PinToolView.cpp View/PinToolView.h ComponentsSDL/SoundFactory.cpp ComponentsSDL/SoundFactory.h)



# Agrego la carpeta con los headers autogenerados a los includes
#message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
#include_directories(${PROJECT_BINARY_DIR})

#install(FILES assets/textures/acidAndButtons.png assets/textures/block.png
#assets/textures/bulletAndRock.png
 #