cmake_minimum_required(VERSION 3.6)
project(Left2Die)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Left2Die ${SOURCE_FILES})

target_link_libraries (Left2Die sfml-graphics sfml-window sfml-system)