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
#include "../states/Context.h"

class GameLoop {
public:
    GameLoop(std::shared_ptr< Game >);
    std::deque<int> input;
    int run(std::shared_ptr<EngineHelper> engine);

    static enum inputEvent {EVENT_LEFTCLICK, EVENT_RIGHTCLICK, EVENT_MIDDLECLICK};
private:
    std::shared_ptr<Game> mGame;
    std::shared_ptr<Context> mStateContext;
};


#endif //ITP4_GAMELOOP_H
