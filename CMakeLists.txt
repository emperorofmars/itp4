cmake_minimum_required(VERSION 3.1)
project(itp4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

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
    src/mgf/mgf_opengl.h
    src/tests/test.cpp
    #src/libs/mlog.h
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

target_link_libraries(itp4 "/home/lukas/.clion10/system/cmake/generated/eab71f22/eab71f22/Debug/libmgf.a")