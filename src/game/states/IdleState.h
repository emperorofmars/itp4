/*
** Author:  Lukas Stanek on 04.06.15.
** File:    IdleState.h
** Project: Turn based Strategy Game
*/

#ifndef ITP4_IDLESTATE_H
#define ITP4_IDLESTATE_H


#include "State.h"

class IdleState : public State{

public:
    virtual void handleEvent(GameLoop::inputEvent event) override;
};


#endif //ITP4_IDLESTATE_H
