cmake_minimum_required(VERSION 3.6)
project(Left2Die)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(SOURCE_FILES src/main.cpp
        src/Game.cpp
        src/Game.h
        src/states/StateBase.h
        src/states/StateBase.cpp
        src/states/StateMachine.cpp
        src/states/StateMachine.h
        src/states/StateMainMenu.cpp
        src/states/StateMainMenu.h
        src/states/StatePlayGame.cpp
        src/states/StatePlayGame.h
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
        src/util/ResourceLoader.h
        src/modules/Player.cpp
        src/modules/Player.h
        src/modules/zombie.cpp
        src/modules/zombie.h src)

find_package (OpenGL REQUIRED)
add_executable(Left2Die ${SOURCE_FILES})

if (UNIX)
    find_library(sfgui NAMES library PATHS /lib/SFGUI-0.1.1-source)
endif(UNIX)

target_link_libraries (Left2Die sfml-graphics sfml-window sfml-system sfml-audio sfgui ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})