cmake_minimum_required(VERSION 3.10)
project(Portal)

set(CMAKE_CXX_STANDARD 11)

add_library(ffmpeg-src
        FormatContext.cpp FormatContext.h
        OutputFormat.cpp OutputFormat.h)

target_link_libraries(ffmpeg-src avformat avcodec avutil swscale)
