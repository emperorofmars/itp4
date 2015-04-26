/*
** Author:  Lukas Stanek
** File:    GameLoop.h
** Project: Turn Based Strategy Game
*/


#ifndef ITP4_GAMELOOP_H
#define ITP4_GAMELOOP_H


#include <deque>
#include "../gameElements/Player.h"
#include "../Game.h"
#include "../EngineHelper.h"

class GameLoop {
public:
    GameLoop(std::shared_ptr< Game >);
    std::deque<int> input;
    int run(std::shared_ptr<EngineHelper> engine);

private:
    std::shared_ptr<Game> mGame;
};


#endif //ITP4_GAMELOOP_H
