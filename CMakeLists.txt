cmake_minimum_required(VERSION 2.8)
project(itp4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories("${CMAKE_SOURCE_DIR}/src/libs/mgf")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/libs/mgf")

SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "./libs")

set(SOURCE_FILES
    src/game/gameElements/Hexfield.h
    src/game/gameElements/Hexfield.cpp
    src/game/gameElements/Player.h
    src/game/gameElements/Player.cpp
    src/game/gameElements/Unit.cpp
    src/game/gameElements/Unit.h
    src/game/gameElements/UnitManager.cpp
    src/game/gameElements/UnitManager.h
    src/game/Game.cpp
    src/game/Game.h
    src/game/startUp.h
    src/game/startUp.cpp
    src/game/gameLoop/GameLoop.h
    src/game/gameLoop/GameLoop.cpp
    src/game/menu/Menu.h
    src/tests/test.cpp
    src/libs/mlog.h
    src/tbs.cpp
    src/tbs.h
    src/game/EngineHelper.cpp
    src/game/EngineHelper.h
    src/game/states/State.cpp
    src/game/states/State.h
    src/game/states/State.cpp
    src/game/states/State.h
    src/game/states/Context.cpp
    src/game/states/Context.h
    src/game/states/State.cpp
    src/game/states/State.h
    src/game/states/IdleState.cpp
    src/game/states/IdleState.h
    src/game/states/SelectedState.cpp
    src/game/states/SelectedState.h
    src/game/states/MovingState.cpp
    src/game/states/MovingState.h
    src/game/states/FightState.cpp
    src/game/states/FightState.h
    src/game/util/constants.h)

add_executable(itp4 ${SOURCE_FILES} src/game/util/ChanceSimulator.cpp src/game/util/ChanceSimulator.h src/game/menu/Menu.cpp src/game/menu/Settings.cpp src/game/menu/Settings.h src/game/menu/MenuLoop.cpp src/game/menu/MenuLoop.h src/game/menu/Credits.cpp src/game/menu/Credits.h)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(itp4 ${SDL2_LIBRARIES})

PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
INCLUDE_DIRECTORIES(${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(itp4 ${SDL2IMAGE_LIBRARIES})

PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
INCLUDE_DIRECTORIES(${SDL2TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(itp4 ${SDL2TTF_LIBRARIES})

PKG_SEARCH_MODULE(GLEW REQUIRED glew)
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(itp4 ${GLEW_LIBRARIES})


PKG_SEARCH_MODULE(ASSIMP REQUIRED assimp)
INCLUDE_DIRECTORIES(${ASSIMP_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(itp4 ${ASSIMP_LIBRARIES})

target_link_libraries(itp4 mgf_lib)