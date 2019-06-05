cmake_minimum_required(VERSION 3.10)
project(Portal)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

add_library(resources
        ProtectedQueue.cpp
        Socket.cpp
        AcceptSocket.cpp)