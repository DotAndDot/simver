cmake_minimum_required(VERSION 3.7)
project(sim)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        log/log.c
        log/log.h
        log/macro_define.h
        Channel.h
        EPoll.cpp
        EPoll.h
        Socket.cpp
        Socket.h)

add_executable(sim ${SOURCE_FILES})