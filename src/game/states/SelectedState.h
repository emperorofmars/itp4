/*
** Author:  Lukas Stanek on 04.06.15.
** File:    SelectedState.h
** Project: Turn based Strategy Game
*/

#ifndef ITP4_SELECTEDSTATE_H
#define ITP4_SELECTEDSTATE_H


#include "State.h"

class SelectedState : public State{


public:
    virtual void handleEvent(InputEvent event) override;

    SelectedState(const std::shared_ptr<Context> &ctx) : State(ctx) { }

protected:
    virtual void handleRightClick() override;

    virtual void handleLeftClick() override;
};


#endif //ITP4_SELECTEDSTATE_H
