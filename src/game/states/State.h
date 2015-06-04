/*
** Author:  Lukas Stanek on 04.06.15.
** File:    State.h
** Project: Turn based Strategy Game
*/

#ifndef ITP4_STATE_H
#define ITP4_STATE_H


#include "../gameLoop/GameLoop.h"

class State {
public:
    virtual void handleEvent(GameLoop::inputEvent);
private:
};


#endif //ITP4_STATE_H
