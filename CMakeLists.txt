cmake_minimum_required(VERSION 3.6)
project(Left2Die)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp
        src/Game.cpp
        src/Game.h
        src/states/StateBase.h
        src/states/StateBase.cpp
        src/states/StateMachine.cpp
        src/states/StateMachine.h
        src/states/StateMainMenu.cpp
        src/states/StateMainMenu.h
        src/states/StateSinglePlayer.cpp
        src/states/StateSinglePlayer.h
        src/states/StateMultiPlayer.cpp
        src/states/StateMultiPlayer.h
        src/states/StateHighScore.cpp
        src/states/StateHighScore.h
        src/states/StateSettings.cpp
        src/states/StateSettings.h
        src/input/InputManager.cpp
        src/input/InputManager.h
        src/input/InputObserver.cpp
        src/input/InputObserver.h
        src/input/InputTester.cpp
        src/input/InputTester.h
        src/util/VectorUtil.h
        src/util/ResourceLoader.cpp
        src/util/ResourceLoader.h)

add_executable(Left2Die ${SOURCE_FILES})

target_link_libraries (Left2Die sfml-graphics sfml-window sfml-system sfgui)