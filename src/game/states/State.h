/*
** Author:  Lukas Stanek on 04.06.15.
** File:    State.h
** Project: Turn based Strategy Game
*/

#ifndef ITP4_STATE_H
#define ITP4_STATE_H


#include "../gameLoop/GameLoop.h"
#include "../constants.h"

class Context;
class GameLoop;

class State {
public:
    State(std::shared_ptr<Context> ctx);
    ~State();
    virtual void handleEvent(InputEvent);
    void setGame(std::shared_ptr<Game>);
    std::string getName();
protected:
    std::shared_ptr<Context> mContext;
    std::shared_ptr<Game> mGame;
    std::string mName;

    virtual void handleLeftClick();

    virtual void handleRightClick();
    void handleMiddleClick();
};


#endif //ITP4_STATE_H
