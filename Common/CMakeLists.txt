cmake_minimum_required(VERSION 3.10)
project(Portal)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

add_subdirectory(ProtocolTranslator)

add_library(common-src
        ProtectedBlockingQueue.h
        SafeQueue.h
        Socket.cpp
        AcceptSocket.cpp
        Thread.cpp
        Protocol.cpp Protocol.h)

target_link_libraries(common-src protocol-translator)