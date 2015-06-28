/*
** Author:  Lukas Stanek
** File:    GameLoop.h
** Project: Turn Based Strategy Game
*/


#ifndef ITP4_GAMELOOP_H
#define ITP4_GAMELOOP_H


#include <deque>
#include <string>
#include "../gameElements/Player.h"
#include "../Game.h"
#include "../EngineHelper.h"
#include "../states/Context.h"

class Context;

class GameLoop {
public:
    GameLoop(std::shared_ptr <Game>);
    ~GameLoop();

    std::deque <int> input;

    int run(std::shared_ptr <EngineHelper> engine);

private:
    std::shared_ptr <Game> mGame;
    std::shared_ptr <Context> mStateContext;

    bool gameFinished();

    bool checkOutOfBounds(glm::vec3 tvec3);
};


#endif //ITP4_GAMELOOP_H
