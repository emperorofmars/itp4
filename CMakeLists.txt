cmake_minimum_required(VERSION 2.8)
project(itp4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")


include_directories("/home/lukas/repos/mgf")


set(SOURCE_FILES
    src/game/gameElements/Field.h
    src/game/gameElements/Hexfield.h
    src/game/gameElements/Hexfield.cpp
    src/game/gameElements/Moveable.h
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
    src/tbs.h)

add_executable(itp4 ${SOURCE_FILES} src/game/EngineHelper.cpp src/game/EngineHelper.h)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(itp4 ${SDL2_LIBRARIES})

PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
INCLUDE_DIRECTORIES(${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(itp4 ${SDL2IMAGE_LIBRARIES})


PKG_SEARCH_MODULE(GLEW REQUIRED glew)
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(itp4 ${GLEW_LIBRARIES})


PKG_SEARCH_MODULE(ASSIMP REQUIRED assimp)
INCLUDE_DIRECTORIES(${ASSIMP_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(itp4 ${ASSIMP_LIBRARIES})

target_link_libraries(itp4 "${CMAKE_SOURCE_DIR}/src/libs/libmgf_lib.a")