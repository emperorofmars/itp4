/*
** Author:  Lukas Stanek on 04.06.15.
** File:    FightState.h
** Project: Turn based Strategy Game
*/

#ifndef ITP4_FIGHTSTATE_H
#define ITP4_FIGHTSTATE_H


#include "State.h"

class FightState : public State{

public:
    FightState(const std::shared_ptr<Context> &ctx) : State(ctx) {
        mName = "FIGHTING";
    }
};


#endif //ITP4_FIGHTSTATE_H
