/*
** Author:  Lukas Stanek
** File:    GameLoop.h
** Project: Turn Based Strategy Game
*/


#ifndef ITP4_GAMELOOP_H
#define ITP4_GAMELOOP_H


#include "../gameElements/Player.h"
#include "../Game.h"

class GameLoop {
public:
    GameLoop(Game);
    Player run();

private:
    std::shared_ptr<Game> mGame;
};


#endif //ITP4_GAMELOOP_H
