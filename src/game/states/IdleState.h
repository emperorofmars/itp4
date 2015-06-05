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
    IdleState(const std::shared_ptr<Context> &ctx) : State(ctx) {
        mName = "IDLE";
    }

    virtual void handleEvent(InputEvent event) override;

protected:
    virtual void handleLeftClick() override;
};


#endif //ITP4_IDLESTATE_H
