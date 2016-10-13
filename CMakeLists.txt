cmake_minimum_required(VERSION 3.6)
project(Left2Die)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        states/StateBase.h
        states/StateBase.cpp
        states/StateMachine.cpp
        states/StateMachine.h
        states/StateMainMenu.cpp states/StateMainMenu.h util/ResourceLoader.cpp util/ResourceLoader.h Game.cpp Game.h states/StateSinglePlayer.cpp states/StateSinglePlayer.h states/StateMultiPlayer.cpp states/StateMultiPlayer.h states/StateHighScore.cpp states/StateHighScore.h states/StateSettings.cpp states/StateSettings.h)
add_executable(Left2Die ${SOURCE_FILES})

target_link_libraries (Left2Die sfml-graphics sfml-window sfml-system)