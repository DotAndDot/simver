cmake_minimum_required(VERSION 3.7)
project(simver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        log/log.cpp
        log/log.h
        log/macro_define.h
        Channel.h
        EPoll.cpp
        EPoll.h
        Socket.cpp
        Socket.h Channel.cpp EventLoop.h EventLoop.cpp Connection.h Connection.cpp Server.h Server.cpp Buffer.h Buffer.cpp)

add_executable(sim ${SOURCE_FILES})