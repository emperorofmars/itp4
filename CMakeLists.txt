cmake_minimum_required(VERSION 3.1)
project(itp4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/game/gameElements/Field.h
    src/game/gameElements/Hexfield.h
    src/game/gameElements/Moveable.h
    src/game/menu/Menu.h
    src/mgf/mgf_opengl.h
    src/tests/test.cpp
    src/libs/mlog.h
    src/tbs.cpp
    src/tbs.h)

add_executable(itp4 ${SOURCE_FILES} src/game/gameElements/Player.cpp src/game/gameElements/Player.h src/game/gameElements/Unit.cpp src/game/gameElements/Unit.h src/game/gameElements/UnitManager.cpp src/game/gameElements/UnitManager.h src/game/Game.cpp src/game/Game.h src/game/gameLoop/GameLoop.cpp src/game/gameLoop/GameLoop.h)