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
        src/input/PlayerController.cpp
        src/input/PlayerController.h
        src/util/VectorUtil.h
        src/util/ResourceLoader.cpp
        src/util/ResourceLoader.h
        src/entities/Player.cpp
        src/entities/Player.h
        src/entities/enemies/zombie.cpp
        src/entities/enemies/zombie.h
        src/states/StateShop.cpp
        src/states/StateShop.h
        src/states/StateGameOver.cpp
        src/states/StateGameOver.h
        src/gui/Message.cpp
        src/gui/Message.h
        src/entities/Entity.h
        src/entities/Weapon.cpp
        src/entities/Weapon.h
        src/entities/Projectile.cpp
        src/entities/Projectile.h
        src/entities/enemies/Enemy.cpp
        src/entities/enemies/Enemy.h
        src/entities/enemies/NormalZombie.cpp
        src/entities/enemies/NormalZombie.h
        src/entities/enemies/CrawlingZombie.cpp
        src/entities/enemies/CrawlingZombie.h
        src/level/Level.cpp
        src/level/Level.h
        src/level/tiles/TileBase.h
        src/level/tiles/TileBase.cpp
        src/level/tiles/TileStone.cpp
        src/level/tiles/TileStone.h
        src/level/tiles/TileDirt.cpp
        src/level/tiles/TileDirt.h
        src/world/World.cpp
        src/world/World.h)

find_package (OpenGL REQUIRED)
add_executable(Left2Die ${SOURCE_FILES})

if (UNIX)
    find_library(sfgui NAMES library PATHS /lib/SFGUI-0.1.1-source)
endif(UNIX)

target_link_libraries (Left2Die sfml-graphics sfml-window sfml-system sfml-audio sfgui ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})