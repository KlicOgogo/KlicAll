cmake_minimum_required(VERSION 3.7)
project(Lab1)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(SOURCE_FILES main.cpp)

add_executable(Lab1 ${SOURCE_FILES})