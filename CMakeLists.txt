cmake_minimum_required(VERSION 3.6)
project(a3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Graph.h
        main.cpp)

add_executable(a3 ${SOURCE_FILES})