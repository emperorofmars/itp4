/*
** Author:  Lukas Stanek on 04.06.15.
** File:    MovingState.h
** Project: Turn based Strategy Game
*/

#ifndef ITP4_MOVINGSTATE_H
#define ITP4_MOVINGSTATE_H


#include "State.h"

class MovingState : public State {

public:
    MovingState(const std::shared_ptr<Context> &ctx) : State(ctx) { }
};


#endif //ITP4_MOVINGSTATE_H
